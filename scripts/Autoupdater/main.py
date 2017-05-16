import pyurmc
import pyurlaser
import pyurio
import sys
import os
from distutils.version import StrictVersion
from ctypes import byref
from subprocess import call

DEFAULT_PATH = os.path.join("/", "dev")

libraries = {
    'urio': pyurio,
    'urlaser': pyurlaser,
    'urmc': pyurmc
}

devices = libraries.keys()

lib = None

# debug
NUMBER_OF_ARGS = 1
firmware = "urio-1.2.3-hw2.3.x.cod"
DEFAULT_PATH = "."


class Return:
    Error = -1
    Ok = 0


class Library:
    def __init__(self, name):
        self._name = name
        self._pymodule = libraries[name]
        self._prefix = name + "_"
        self._lib = libraries[name].project_shared_lib()

    @property
    def pymodule(self):
        return self._pymodule

    @property
    def name(self):
        return self._name

    def __getattr__(self, item):
        return self._lib.__getitem__(self._prefix + item)


class Device:
    global lib

    def __init__(self, path):
        self._path = path
        self._device_id = None
        self.serial = None
        self.hardware = None
        self.firmware = None

    @staticmethod
    def device_uri(name):
        # debug
        return ("emu:///" + name).encode()

    def open(self):
        global lib
        self._device_id = lib.open_device(Device.device_uri(self._path))
        return self._device_id

    def close(self):
        global lib
        lib.close_device(self._device_id)

    def get_serial(self):
        # unfortunately, there are no standard for getting serial in protocol
        # special call for urmc is necessary
        global lib
        if lib.name == 'urmc':
            identity = lib.pymodule.get_serial_number_t()
            result = lib.get_serial_number(self._device_id, byref(identity))
            if result != lib.pymodule.Result.Ok:
                error("ошибка {0} при получении серийного номера".format(result))
                return Return.Error
            self.serial = identity.SerialNumber
            return self.serial

        # urio, urlaser
        identity = lib.pymodule.get_identity_information_t()
        result = lib.get_identity_information(self._device_id, byref(identity))
        if result != lib.pymodule.Result.Ok:
            error("ошибка {0} при получении серийного номера".format(result))
            return Return.Error

        self.serial = identity.SerialNumber
        return self.serial

    def get_firmware_version(self):
        # unfortunately, there are no standard for getting version in protocol
        # special call for urmc is necessary
        global lib
        if lib.name == 'urmc':
            identity = lib.pymodule.firmware_version_t()
            result = lib.firmware_version(self._device_id, byref(identity))
            if result != lib.pymodule.Result.Ok:
                error("ошибка {0} при получении версии прошивки".format(result))
                return Return.Error
            self.firmware = "{0}.{1}.{2}".format(identity.Major, identity.Minor, identity.Bugfix)
            return self.firmware

        # urio, urlaser
        identity = lib.pymodule.get_identity_information_t()
        result = lib.get_identity_information(self._device_id, byref(identity))
        if result != lib.pymodule.Result.Ok:
            error("ошибка {0} при получении версии прошивки".format(result))
            return Return.Error
        self.firmware = "{0}.{1}.{2}".format(identity.FirmwareMajor, identity.FirmwareMinor, identity.FirmwareBugfix)
        return self.firmware

    def get_hardware_version(self):
        # unfortunately, there are no standard for getting version in protocol
        # special call for urmc is necessary
        global lib
        if lib.name == 'urmc':
            identity = lib.pymodule.device_information_impl_t()
            result = lib.device_information_impl(self._device_id, byref(identity))
            if result != lib.pymodule.Result.Ok:
                error("ошибка {0} при получении версии железа".format(result))
                return Return.Error
            self.hardware = "{0}.{1}.{2}".format(identity.Major, identity.Minor, identity.Bugfix)
            return self.hardware

        # urio, urlaser
        identity = lib.pymodule.get_identity_information_t()
        result = lib.get_identity_information(self._device_id, byref(identity))
        if result != lib.pymodule.Result.Ok:
            error("ошибка {0} при получении версии железа".format(result))
            return Return.Error

        self.hardware = "{0}.{1}.{2}".format(identity.HardwareMajor, identity.HardwareMinor, identity.HardwareBugfix)
        return self.hardware

    def epc_boot(self, firmware):
        return call("epcboot -F -a {port} -f {file}".format(port=Device.device_uri(self._path), file=firmware))


def critical_error(str):
    print("Критическая ошибка: {0}".format(str))
    exit(1)


def error(str):
    print("Ошибка: {0}".format(str))


def parse_name(str):
    # format: urmc-1.2.3-hw2.3.x.cod
    try:
        name, version, hardware = str.split("-", 2)
    except ValueError:
        critical_error("неправильное имя файла")

    return name, version, hardware


def check_hardware(mask, version):
    # format: hw2.3.x.cod
    temp_mask = mask[2:][:-4]
    try:
        if False in list(map(lambda x, y: x == y or x == 'x', temp_mask.split('.'), version.split('.'))):
            return False
    except ValueError:
        return False

    return True


def check_firmware(version1, version2):
    # format: 1.2.3
    # version2 must be older them version1
    return StrictVersion(version1) > StrictVersion(version2)


print("Автозагрузчик")

if len(sys.argv) != NUMBER_OF_ARGS:
    critical_error("неправильные аргументы")

# firmware = sys.argv[1]

module_name, firmware_version, hardware_version = parse_name(firmware)

print("\nИмя устройства: ", module_name)
print("Версия прошивки: ", firmware_version)
print("Версия железа: ", hardware_version)

if module_name not in devices:
    critical_error("{name} нет в списке известных устройств".format(name=module_name))

print("\nПоиск устройств {name} ...".format(name=module_name))

path = os.path.join(DEFAULT_PATH, module_name)

if not os.path.exists(path):
    critical_error("не обнаружено устройств {name} (файл не существует)".format(name=module_name))

if not os.path.isdir(path):
    critical_error("файл {name} не является каталогом устройств".format(name=path))

device_list = [Device(os.path.join(path, n)) for n in os.listdir(path)]

print("Найдено {0} устройств {name}".format(len(device_list), name=module_name))

print("\nЗагрузка библиотеки для {0}...".format(module_name))

try:
    lib = Library(module_name)
except OSError as err:
    critical_error("не удаётся загрузить библиотеку")

print("\nСбор сведений об устройствах ...")
for device in device_list.copy():

    if device.open() < 0:
        error("Невозожно открыть устройство {0}, пропуск".format(device))
        device_list.remove(device)
        continue

    if device.get_serial() == Return.Error:
        error("Не удалось получить серийный номер для {0}, пропуск".format(device))
        device_list.remove(device)
        continue

    if device.get_hardware_version() == Return.Error:
        error("Не удалось получить версию железа для {0}, пропуск".format(device.serial))
        device_list.remove(device)
        continue

    if not check_hardware(hardware_version, device.hardware):
        print("Не совпадают версии железа для {0}".format(device.serial))
        print("Версия железа: {0}, требуется: {1}, пропуск".format(device.hardware, hardware_version))
        device_list.remove(device)
        continue

    if device.get_firmware_version() == Return.Error:
        error("Не удалось получить версию прошивки для {0}, пропуск".format(device.serial))
        device_list.remove(device)
        continue

    if not check_firmware(firmware_version, device.firmware):
        print("Устройство {0} не нуждается в обновлении, пропуск".format(device.serial))
        device_list.remove(device)
        continue

    device.close()

print("\nОбновление...")
print("Устройств для обновления: {0}".format(len(device_list)))
if not len(device_list):
    print("Нет устройств для обновления, выход")
    exit()

for device in device_list.copy():
    print("Обновление {0}".format(device.serial))
    status = device.epc_boot(firmware)
    if status == Return.Ok:
        print("Успех")
    else:
        error("обновление завершилось с кодом {0}".format(status))
        device_list.remove(device)
        continue

print("\nВсего обновлено: {0} устройств".format(len(device_list)))
print(*[device.serial for device in device_list.sort(reverse=True)])
