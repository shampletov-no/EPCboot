#ifndef INC_BOOTLOADER_H
#define INC_BOOTLOADER_H

#include "api.h"

#include <time.h>

#include "commands.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define WKEY_SIZE 32

/**
    * \~english
    * 
    * @param[in] id device identifier
    * \~russian
    * Программная перезагрузка
    * @param[in] id идентификатор устройства
    */
result_t URPC_CALLCONV reset(device_t id);

/**
    * \~english
    * Write command key to decrypt the firmware. Result = RESULT_OK, if the command loader. Result = RESULT_HARD_ERROR, if at the time of the command there was mistake. Can be used by manufacturer only.
    * @param[in] id device identifier
    * @param[in] input Function call arguments
    * @param[out] output Function call result storage
    * \~russian
    * Команда записи ключа для расшифровки прошивки. Result = RESULT_OK, если команда выполнена загрузчиком. Result = RESULT_HARD_ERROR, если во время выполнения команды произошла ошибка. Функция используется только производителем.
    * @param[in] id идентификатор устройства
    * @param[in] input Входные аргументы вызова
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV write_key(device_t id, in_write_key_t* input, out_write_key_t* output);

/**
    * \~english
    * 
    * @param[in] id device identifier
    * @param[in] input Function call arguments
    * @param[out] output Function call result storage
    * \~russian
    * Начать сессию обновления прошивки
    * @param[in] id идентификатор устройства
    * @param[in] input Входные аргументы вызова
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV start_session(device_t id, in_start_session_t* input, out_start_session_t* output);

/**
    * \~english
    * 
    * @param[in] id device identifier
    * @param[in] input Function call arguments
    * @param[out] output Function call result storage
    * \~russian
    * Закончить сессию обновления прошивки
    * @param[in] id идентификатор устройства
    * @param[in] input Входные аргументы вызова
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV end_session(device_t id, in_end_session_t* input, out_end_session_t* output);

/**
    * \~english
    * 
    * @param[in] id device identifier
    * @param[in] input Function call arguments
    * \~russian
    * Запись данных
    * @param[in] id идентификатор устройства
    * @param[in] input Входные аргументы вызова
    */
result_t URPC_CALLCONV write_data(device_t id, write_data_t* input);

/**
    * \~english
    * This command is deprecated. It is saved in the protocol for backwards compatibility. The new devices use the command ginf.
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Эта команда считается устаревшей. Сохраняется в протоколе для обратной совместимости. В новых устройствах следует использовать команду ginf.
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV get_device_information(device_t id, get_device_information_t* output);

/**
    * \~english
    * This command is deprecated. It is saved in the protocol for backwards compatibility. The new devices use the command ginf.
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Эта команда считается устаревшей. Сохраняется в протоколе для обратной совместимости. В новых устройствах следует использовать команду ginf.
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV get_bootloader_version(device_t id, get_bootloader_version_t* output);

/**
    * \~english
    * 
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Проверка CRC всей прошивки
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV has_firmware(device_t id, has_firmware_t* output);

/**
    * \~english
    * 
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Проверка CRC и установка флага готовности переходата на прошивку
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV goto_firmware(device_t id, goto_firmware_t* output);

/**
    * \~english
    * Set internal random number in controller and read it. Should be used by manufacturer only.
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Установка внутреннего случайного числа контроллера и чтение его. Должно использоваться только производителем.
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV init_random(device_t id, init_random_t* output);

/**
    * \~english
    * Write device serial number and hardware version to controller's flash memory. Along with the new serial number and hardware version a "Key" is transmitted. The SN and hardware version are changed and saved when keys match. Can be used by manufacturer only.
    * @param[in] id device identifier
    * @param[in] input Function call arguments
    * \~russian
    * Запись серийного номера и версии железа во flash память контроллера. Вместе с новым серийным номером и версией железа передаётся "Ключ", только при совпадении которого происходит изменение и сохранение. Функция используется только производителем.
    * @param[in] id идентификатор устройства
    * @param[in] input Входные аргументы вызова
    */
result_t URPC_CALLCONV set_serial_number(device_t id, set_serial_number_t* input);

/**
    * \~english
    * This command is deprecated. It is saved in the protocol for backwards compatibility. The new devices use the command ginf.
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Эта команда считается устаревшей. Сохраняется в протоколе для обратной совместимости. В новых устройствах следует использовать команду ginf.
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV get_serial_number(device_t id, get_serial_number_t* output);

/**
    * \~english
    * This command is deprecated. It is saved in the protocol for backwards compatibility. The new devices use the command rbld.
    * @param[in] id device identifier
    * \~russian
    * Эта команда считается устаревшей. Сохраняется в протоколе для обратной совместимости. В новых устройствах следует использовать команду rbld.
    * @param[in] id идентификатор устройства
    */
result_t URPC_CALLCONV update_firmware(device_t id);

/**
    * \~english
    * This command is deprecated. It is saved in the protocol for backwards compatibility. In bootloader mode it does nothing useful.
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Эта команда считается устаревшей. Сохраняется в протоколе для обратной совместимости. Если находимся в режиме bootloader, то ничего полезного не делает.
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV get_status(device_t id, get_status_t* output);

/**
    * \~english
    * Return device identity information such as firmware version and serial number. It is useful to find your device in a list of available devices. It can be called from the firmware and bootloader.
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Возвращает идентификационную информацию об устройстве, такую как номера версий прошивки и серийный номер. Эта информация удобна для поиска нужного устройства среди списка доступных. Может быть вызвана как из прошивки, так и из бутлоадера.
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV get_identity_information(device_t id, get_identity_information_t* output);

/**
    * \~english
    * This command reboots the controller to the bootloader. After receiving this command, the firmware sets a flag (for bootloader), sends reply and restarts the controller.
    * @param[in] id device identifier
    * \~russian
    * Команда служит для перезагрузки контроллера в загрузчик. Получив такую команду, прошивка платы устанавливает флаг (для загрузчика), отправляет ответ и перезагружает контроллер.
    * @param[in] id идентификатор устройства
    */
result_t URPC_CALLCONV reboot_to_bootloader(device_t id);

/**
    * \~english
    * Dummy command, because accessors must be.
    * @param[in] id device identifier
    * @param[out] output Function call result storage
    * \~russian
    * Команда пустышка, потому что аксессоры должны быть.
    * @param[in] id идентификатор устройства
    * @param[out] output Хранилище для результатов вызова
    */
result_t URPC_CALLCONV get_dummy(device_t id, dummy_t* output);

/**
    * \~english
    * Dummy command, because accessors must be.
    * @param[in] id device identifier
    * @param[in] input Function call arguments
    * \~russian
    * Команда пустышка, потому что аксессоры должны быть.
    * @param[in] id идентификатор устройства
    * @param[in] input Входные аргументы вызова
    */
result_t URPC_CALLCONV set_dummy(device_t id, dummy_t* input);

/**
	* \~english
	* Open a device with OS name \a name and return identifier of the device which can be used in calls.
	* @param[in] name a device name
	* Device name has form "com:port", or "emu:file" for virtual device.
    * Now in case of virtual port open_device returns only one virtual device at each call.
	* In case of USB-COM port the "port" is the OS device name.
	* For example:
    *   "com:///\\.\COM12",
    *   "com:\\.\COM12",
    *   "com:///dev/tty/ttyACM34",
    *   "emu:///var/lib/ximc/virtual56.dat",
    *   "emu:///c:/temp/virtual56.dat",
    *   "emu:///c:/temp/virtual56.dat?serial=123"
	* \~russian
	* Открывает устройство по имени \a name и возвращает идентификатор, который будет использоваться для обращения к устройству.
	* @param[in] name - имя устройства
	* Имя устройства имеет вид "com:port" или "emu:file" для виртуального устройства.
    * Сейчас open_device возвращает только одно устройство при каждом вызове.
	* Для USB-COM устройства "port" это имя устройства в ОС.
	* Например:
    *   "com:///\\.\COM12",
    *   "com:\\.\COM12",
    *   "com:///dev/tty/ttyACM34",
    *   "emu:///var/lib/ximc/virtual56.dat",
    *   "emu:///c:/temp/virtual56.dat",
    *   "emu:///c:/temp/virtual56.dat?serial=123"
	*/
device_t URPC_CALLCONV open_device (const char* name);

/**
	* \~english
	* Close specified device
	* @param id an identifier of device
	* \~russian
	* Закрывает устройство
	* @param id - идентификатор устройства
	*/
result_t URPC_CALLCONV close_device (device_t* id);

/**
	* \~english
	* Reset library locks in a case of deadlock.
	* \~russian
	* Снимает блокировку библиотеки в экстренном случае.
	*/
result_t URPC_CALLCONV reset_locks ();

/**
	* \~english
	* Fix for errors in Windows USB driver stack.
	* USB subsystem on Windows does not always work correctly. The following bugs are possible:
	* the device cannot be opened at all, or
	* the device can be opened and written to, but it will not respond with data.
	* These errors can be fixed by device reconnection or removal-rescan in device manager.
	* bootloader_fix_usbser_sys() is a shortcut function to do the remove-rescan process.
	* You should call this function if bootloader library cannot open the device which was not physically removed from the system or if the device does not respond.
	* \~russian
	* Исправление ошибки драйвера USB в Windows.
	* Подсистема USB-COM на Windows не всегда работает корректно. При работе возможны следующие неисправности:
	* все попытки открыть устройство заканчиваются неудачно, или
	* устройство можно открыть и писать в него данные, но в ответ данные не приходят.
	* Эти проблемы лечатся переподключением устройства или удалением и повторным поиском устройства в диспетчере устройств.
	* Функция bootloader_fix_usbser_sys() автоматизирует процесс удаления-обнаружения.
	* Имеет смысл вызывать эту функцию, если библиотека не может открыть устройство, при том что оно физически не было удалено из системы, или если устройство не отвечает.
	*/
result_t URPC_CALLCONV bootloader_fix_usbser_sys(const char* device_name);

/**
	* \~english
	* Sleeps for a specified amount of time
	* @param msec time in milliseconds
	* \~russian
	* Приостанавливает работу на указанное время
	* @param msec время в миллисекундах
	*/
void URPC_CALLCONV msec_sleep (unsigned int msec);

/**
	* \~english
	* Returns a library version
	* @param version a buffer to hold a version string, 32 bytes is enough
	* \~russian
	* Возвращает версию библиотеки
	* @param version буфер для строки с версией, 32 байт достаточно
	*/
void URPC_CALLCONV bootloader_version (char* version);

/**
 * \~english
 * Encripted of main device key
 * @param irnd an random short key
 * @param key is a key for encripted. At end of function it must to be encripted.
 * @return result_ok if success.
 * \~russian
 * Шифрование основного ключа
 * @param irnd случайный короткий ключ
 * @param key ключ для шифрования. На выходе из процедуры должен быть зашифрован.
 * @return result_ok в случае успеха.
 */
result_t URPC_CALLCONV encrypted_key(init_random_t *irnd, in_write_key_t *key);

#if !defined(MATLAB_IMPORT) && !defined(LABVIEW64_IMPORT) && !defined(LABVIEW32_IMPORT)
#include <wchar.h>
/**
	* \~english
	* Logging callback prototype
	* @param loglevel a loglevel
	* @param message a message
	* \~russian
	* Прототип функции обратного вызова для логирования
	* @param loglevel уровень логирования
	* @param message сообщение
	*/
typedef void (URPC_CALLCONV *logging_callback_t)(int loglevel, const wchar_t* message, void* user_data);

/**
	* \~english
	* Simple callback for logging to stderr in wide chars
	* @param loglevel a loglevel
	* @param message a message
	* \~russian
	* Простая функция логирования на stderr в широких символах
	* @param loglevel уровень логирования
	* @param message сообщение
	*/
void URPC_CALLCONV logging_callback_stderr_wide(int loglevel, const wchar_t* message, void* user_data);

/**
	* \~english
	* Simple callback for logging to stderr in narrow (single byte) chars
	* @param loglevel a loglevel
	* @param message a message
	* \~russian
	* Простая функция логирования на stderr в узких (однобайтных) символах
	* @param loglevel уровень логирования
	* @param message сообщение
	*/
void URPC_CALLCONV logging_callback_stderr_narrow(int loglevel, const wchar_t* message, void* user_data);

/**
	* \~english
	* Sets a logging callback.
	* Call resets a callback to default (stderr, syslog) if NULL passed.
	* @param logging_callback a callback for log messages
	* \~russian
	* Устанавливает функцию обратного вызова для логирования.
	* Вызов назначает стандартный логгер (stderr, syslog), если передан NULL
	* @param logging_callback указатель на функцию обратного вызова
	*/
void URPC_CALLCONV set_logging_callback(logging_callback_t logging_callback, void* user_data);

#endif

#if defined(__cplusplus)
};
#endif

#endif
