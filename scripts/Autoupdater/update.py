import pyurmc
import pyurlaser
import pyurio
import sys
import os
from distutils.version import StrictVersion
from ctypes import byref, cast, POINTER, c_int
from subprocess import call
from os import devnull

DEFAULT_PATH = os.path.join("/", "dev")
NUMBER_OF_ARGS = 2

libraries = {
    'urio': pyurio,
    'urlaser': pyurlaser,
    'urmc': pyurmc
}

devices = libraries.keys()

lib = None


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
        return ("com:///" + name).encode()

    def __str__(self):
        if self.serial is None:
            return str(self._path)
        else:
            return str(self.serial)

    def open(self):
        global lib
        self._device_id = lib.open_device(Device.device_uri(self._path))
        return self._device_id

    def close(self):
        global lib
        lib.close_device(byref(cast(self._device_id, POINTER(c_int))))

    def get_serial(self):
        # unfortunately, there are no standard for getting serial in protocol
        # special call for urmc is necessary
        global lib
        if lib.name == 'urmc':
            identity = lib.pymodule.get_serial_number_t()
            result = lib.get_serial_number(self._device_id, byref(identity))
            if result != lib.pymodule.Result.Ok:
                error("error {0} while getting serial".format(result))
                return Return.Error
            self.serial = identity.SerialNumber
            return self.serial

        # urio, urlaser
        identity = lib.pymodule.get_identity_information_t()
        result = lib.get_identity_information(self._device_id, byref(identity))
        if result != lib.pymodule.Result.Ok:
            error("error {0} while getting serial".format(result))
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
                error("error {0} while getting firmware version".format(result))
                return Return.Error
            self.firmware = "{0}.{1}.{2}".format(identity.Major, identity.Minor, identity.Release)
            return self.firmware

        # urio, urlaser
        identity = lib.pymodule.get_identity_information_t()
        result = lib.get_identity_information(self._device_id, byref(identity))
        if result != lib.pymodule.Result.Ok:
            error("error {0} while getting firmware version".format(result))
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
                error("error {0} while getting hardware version".format(result))
                return Return.Error
            self.hardware = "{0}.{1}.{2}".format(identity.Major, identity.Minor, identity.Release)
            return self.hardware

        # urio, urlaser
        identity = lib.pymodule.get_identity_information_t()
        result = lib.get_identity_information(self._device_id, byref(identity))
        if result != lib.pymodule.Result.Ok:
            error("error {0} while getting hardware version".format(result))
            return Return.Error

        self.hardware = "{0}.{1}.{2}".format(identity.HardwareMajor, identity.HardwareMinor, identity.HardwareBugfix)
        return self.hardware

    def epc_boot(self, firmware):
        return call(["epcboot", "-F", "-a", Device.device_uri(self._path), "-f", firmware],
                    stdout=open(devnull, 'w'),
                    stderr=open(devnull, 'w'))


def critical_error(str):
    print("Critical error: {0}".format(str))
    exit(1)


def error(str):
    print("Error: {0}".format(str))


def log(str):
    print(str)


def parse_name(str):
    # format: urmc-1.2.3-hw2.3.x.cod
    str = os.path.basename(str)
    try:
        name, version, hardware = str.split("-", 2)
    except ValueError:
        critical_error("wrong file name")

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


log("Autoupdater")

if len(sys.argv) != NUMBER_OF_ARGS:
    critical_error("wrong arguments")

firmware = sys.argv[1]

module_name, firmware_version, hardware_version = parse_name(firmware)

print("\n")
log("Device name: {0}".format(module_name))
log("Firmware version: {0}".format(firmware_version))
log("Hardware version: {0}".format(hardware_version))

if module_name not in devices:
    critical_error("{name} unknown device name".format(name=module_name))

print("\n")
log("Search device {name} ...".format(name=module_name))

path = os.path.join(DEFAULT_PATH, module_name)

if not os.path.exists(path):
    critical_error("no devices {name} (file not exist)".format(name=module_name))

if not os.path.isdir(path):
    critical_error("file {name} is not directory".format(name=path))

device_list = [Device(os.path.join(path, n)) for n in os.listdir(path)]

log("Find {0} devices {name}".format(len(device_list), name=module_name))

print("\n")
log("Load library for {0}...".format(module_name))

try:
    lib = Library(module_name)
except OSError as err:
    critical_error("can't load library")

print("\n")
log("Taking information about devices...")
for device in device_list.copy():

    print("\n")
    log("Open {0}".format(device))
    if device.open() < 0:
        error("Can't open device {0}, skip".format(device))
        device_list.remove(device)
        continue

    if device.get_serial() == Return.Error:
        error("Can't take serial {0}, skip".format(device))
        device_list.remove(device)
        continue
    log("Serial: {0}".format(device.serial))

    if device.get_hardware_version() == Return.Error:
        error("Can't take hardware version {0}, skip".format(device))
        device_list.remove(device)
        continue
    log("Hardware: {0}".format(device.hardware))

    if not check_hardware(hardware_version, device.hardware):
        log("Bad hardware version for {0}".format(device))
        log("Hardware: {0}, necessary: {1}, skip".format(device.hardware, hardware_version))
        device_list.remove(device)
        continue

    if device.get_firmware_version() == Return.Error:
        error("Can't take firmware version {0}, skip".format(device))
        device_list.remove(device)
        continue
    log("Firmware: {0}".format(device.firmware))

    if not check_firmware(firmware_version, device.firmware):
        log("Device {0} does not need to be updated, skip".format(device))
        device_list.remove(device)
        continue

    log("Close {0}".format(device))
    device.close()

print("\n")
log("Update...")
log("Devices for update: {0}".format(len(device_list)))
if not len(device_list):
    log("No devices, exit")
    exit()

for device in device_list.copy():
    log("Call EPCBoot for {0}...".format(device))
    status = device.epc_boot(firmware)
    if status == Return.Ok:
        log("Success")
    else:
        error("epcboot return {0}".format(status))
        device_list.remove(device)
        continue

log("\nDevices updated: {0}".format(len(device_list)))
log("Devices: {0}".format(*[device for device in device_list]))

log("Exit")
