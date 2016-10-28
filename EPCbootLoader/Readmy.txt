English
	This console application upload urpc firmware.
	It use unic user API function urpc_firmware_update() of EPCboot library that call controller send message functions:
	rdld (aka updf) for reboot to bootloader from main firmware,
	clous port, 2 sec timeout,
	send  conn, wdat, wdat, ..., wdat, disc,
	rest 

	Usage: Uploader <port url> <data path> [Old]
	Old for using UPDF vs RBLD.

	Port url = 	Device name has form "com:port", or "emu:file" for virtual device.
	In case of USB-COM port the "port" is the OS device name.
	* For example:
	*   "com:///\\.\COM12",
	*   "com:\\.\COM12",
	*   "com:///dev/tty/ttyACM34",
	*   "emu:///var/lib/ximc/virtual56.dat",
	*   "emu:///c:/temp/virtual56.dat",
	*   "emu:///c:/temp/virtual56.dat?serial=123"

	Data path is path to new firmware file that need load to controller.

	If we write "Old" at the end of command the old_dev_flag will be set to 1.
		if old_dev_flag == 1 using UPDF command,
		else                 using RBLD command

	Now this application testeded for Windows 7 only. 
	For using this program you MAST place EPCboot.dll and uploader.exe in the same directory.

	For build this program you need:
	1. Build EPCboot library.
	2. Copy EPCboot.dll, EPCboot.exp and EPCboot.lib files to the directory ..EPCbootLoader\Release.
	3. Build EPCbootLoader.
	-----------------
	For debug version build the debug version of EPCboot and place files to ..EPCbootLoader\Debuge.

	You can test input/output to target device. You mast add environment variable BOOTLOG, set to it path to log file and start programm.



Русский (Russian)
    Это приложение использует urpc_firmware_update() -- единственную функция пользовательского API библиотеки EPCboot, 
	которая внутри себя вызывает функции отправки сообщений контроллеру по алгоритму:
	сначала отсылаем rbld (или её алиас updf), чтобы перезагрузиться из основной прошивки в бутлоадер
	закрываем порт, таймаут секунды 2, открываем порт
	шлем conn, wdat, wdat, ..., wdat, disc
	rest

	Usage: Uploader <port url> <data path> [Old]
	Old for using UPDF vs RBLD.

	port url - имя устройства
	Имя устройства имеет вид "com:port" или "emu:file" для виртуального устройства.
	Для USB-COM устройства "port" это имя устройства в ОС.
	* Например:
	*   "com:///\\.\COM12",
	*   "com:\\.\COM12",
	*   "com:///dev/tty/ttyACM34",
	*   "emu:///var/lib/ximc/virtual56.dat",
	*   "emu:///c:/temp/virtual56.dat",
	*   "emu:///c:/temp/virtual56.dat?serial=123"

	data path -- путь к новой прошивке
	
	Если в конце команды написать Old то old_dev_flag будет установлен в 1.
	-- old_dev_flag = 1 -- старая версия устройства, используется UPDF; 
	                = 0 -- RBLD


	В этой версии приложение собиралось и тестировалось только под Windows 7.
	Она использует EPCboot.dll, которую надо поместить в ту же директорию, что и исполняемый флаг программы.

	СБОРКА программы:
	1) Собрать библиотеку EPCboot.
	2) Скопировать файлы EPCboot.dll, EPCboot.exp и EPCboot.lib в директорию ..EPCbootLoader\Release.
	3) Собрать приложение.

	Для сборки отладочной версии надо собрать отладочную версию библиотеки и поместить вышеуказанные файлы 
	в директорию ..EPCbootLoader\Debuge.


	Обмен с целевым устройством использующий это приложение может быть протестирован следующим образом:
		-- Создаём переменную окружения BOOTLOG,
		-- Помещаем в неё путь к лог-файлу,
		-- Запускаем программу, использующую библиотеку.


