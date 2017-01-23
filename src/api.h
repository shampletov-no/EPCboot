#ifndef API_H
#define API_H

/** @file bootloader.h
* \~english
* @brief Header file for bootloader library
* \~russian
* @brief Заголовочный файл для библиотеки bootloader
*/


/**
* \def URPC_CALLCONV
* \brief Library import macro
* Macros allows to automatically import function from shared library.
* On Windows it automatically expands to dllimport/dllexport depending on usage scenario.
* On Linux GCC it expands to visibility attribute.
*/
#if defined(WIN32) || defined(WIN64) ||  defined(LABVIEW64_IMPORT) || defined(LABVIEW32_IMPORT) || defined(MATLAB_IMPORT)
#define URPC_CALLCONV __stdcall
#endif

#if defined(WIN32) || defined(WIN64) || defined(LABVIEW64_IMPORT) || defined(LABVIEW32_IMPORT) || defined(MATLAB_IMPORT)
#if URPC_EXPORTS
#define URPC_VIS __declspec(dllexport)
#else
#define URPC_VIS __declspec(dllimport)
#endif
#else
#define URPC_VIS __attribute__((visibility("default")))
#endif

/**
* \def URPC_RETTYPE
* \brief Thread return type.
*/
#if defined(WIN32) || defined(WIN64) || defined(LABVIEW64_IMPORT) || defined(LABVIEW32_IMPORT) || defined(MATLAB_IMPORT)
#define URPC_RETTYPE unsigned int
#else
#define URPC_RETTYPE void*
#endif

/**
* \def URPC_CALLCONV
* \brief Library calling convention macros.
*/
#if defined(WIN32) || defined(WIN64) || defined(LABVIEW64_IMPORT) || defined(LABVIEW32_IMPORT) || defined(MATLAB_IMPORT)
#define URPC_CALLCONV __stdcall
#else
#define URPC_CALLCONV
#endif


#if !defined(URPC_NO_STDINT)

#if ( (defined(_MSC_VER) && (_MSC_VER < 1600)) || defined(LABVIEW64_IMPORT) || defined(LABVIEW32_IMPORT)) && !defined(MATLAB_IMPORT)
// msvc types burden
typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

/* labview doesn't speak C99 */
#if defined(LABVIEW64_IMPORT) || defined(LABVIEW32_IMPORT)
typedef unsigned __int64 ulong_t;
typedef __int64 long_t;
#else
typedef unsigned long long ulong_t;
typedef long long long_t;
#endif

#endif

#if defined(__cplusplus)
extern "C"
{
#endif


	/**
	* \~english
	* Type describes device identifier
	* \~russian
	* Тип идентификатора устройства
	*/
	typedef int device_t;

	/**
	* \~english
	* Type specifies result of any operation
	* \~russian
	* Тип, определяющий результат выполнения команды.
	*/
	typedef int result_t;

	/**
	* \~english
	* Handle specified undefined device
	* \~russian
	* Макрос, означающий неопределенное устройство
	*/
#define device_undefined -1

	/**
	* \~english
	* @name Result statuses
	* \~russian
	* @name Результаты выполнения команд
	*/
	//@{

	/**
	* \~english
	* success
	* \~russian
	* выполнено успешно
	*/
#define result_ok 0

	/**
	* \~english
	* generic error
	* \~russian
	* общая ошибка
	*/
#define result_error -1

	/**
	* \~english
	* function is not implemented
	* \~russian
	* функция не определена
	*/
#define result_not_implemented -2

	/**
	* \~english
	* value error
	* \~russian
	* ошибка записи значения
	*/
#define result_value_error -3

	/**
	* \~english
	* device is lost
	* \~russian
	* устройство не подключено
	*/
#define result_nodevice -4

	//@}

	/**
	* \~english
	* @name Logging level
	* \~russian
	* @name Уровень логирования
	*/
	//@{

	/**
	* \~english
	* Logging level - error
	* \~russian
	* Уровень логирования - ошибка
	*/
#define LOGLEVEL_ERROR 		0x01
	/**
	* \~english
	* Logging level - warning
	* \~russian
	* Уровень логирования - предупреждение
	*/
#define LOGLEVEL_WARNING 	0x02
	/**
	* \~english
	* Logging level - info
	* \~russian
	* Уровень логирования - информация
	*/
#define LOGLEVEL_INFO		0x03
	/**
	* \~english
	* Logging level - debug
	* \~russian
	* Уровень логирования - отладка
	*/
#define LOGLEVEL_DEBUG		0x04
	//@}

/**
	* \~english
	* The unic user API function that call controller send message functions:
	*	rdld (aka updf) for reboot to bootloader from main firmware,
	*   clous port, 2 sec timeout,
	*   send  conn, wdat, wdat, ..., wdat, disc
	*   rest 
	* @param[in] name a device name
	* Device name has form "com:port", or "emu:file" for virtual device.
	* In case of USB-COM port the "port" is the OS device name.
	* For example:
	*   "com:///\\.\COM12",
	*   "com:\\.\COM12",
	*   "com:///dev/tty/ttyACM34",
	*   "emu:///var/lib/ximc/virtual56.dat",
	*   "emu:///c:/temp/virtual56.dat",
	*   "emu:///c:/temp/virtual56.dat?serial=123"
	* @param[in] data is new firware code
	* @param[in] len is length of data
	* @param[in] old_dev_flag
	*
	* \~russian
	* Единственная функция пользовательского API, которая внутри себя вызывает функции отправки сообщений контроллеру по алгоритму:
	*	сначала отсылаем rbld (или её алиас updf), чтобы перезагрузиться из основной прошивки в бутлоадер
	*	закрываем порт, таймаут секунды 2, открываем порт
	*	шлем conn, wdat, wdat, ..., wdat, disc
	*	rest
	* @param[in] name - имя устройства
	* Имя устройства имеет вид "com:port" или "emu:file" для виртуального устройства.
	* Для USB-COM устройства "port" это имя устройства в ОС.
	* Например:
	*   "com:///\\.\COM12",
	*   "com:\\.\COM12",
	*   "com:///dev/tty/ttyACM34",
	*   "emu:///var/lib/ximc/virtual56.dat",
	*   "emu:///c:/temp/virtual56.dat",
	*   "emu:///c:/temp/virtual56.dat?serial=123"
	* @param[in] data -- новая прошивка
	* @param[in] len -- длина новой прошивки в байтах
	* @param[in] old_dev_flag = 1 -- старая версия устройства, используется UPDF; = 0 -- RBLD
	*/
	URPC_VIS result_t URPC_CALLCONV urpc_firmware_update(const char* name, const uint8_t* data, int len);

    URPC_VIS result_t URPC_CALLCONV urpc_write_key(const char* name, const char* key);

    URPC_VIS result_t URPC_CALLCONV urpc_write_ident(const char* name, const char* key, unsigned int serial, char* hard_id);

#if defined(__cplusplus)
};
#endif

#endif /*API_H*/



