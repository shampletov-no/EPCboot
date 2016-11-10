**English**
This console application upload urpc firmware.
It use unic user API function urpc_firmware_update() of EPCboot library that call controller send message functions:

    rdld (aka updf) for reboot to bootloader from main firmware,
    close port, 2 sec timeout,
    send  conn, wdat, wdat, ..., wdat, disc,
    rest 

*Usage*: `Uploader <port url> <data path> [Old]`
Old for using UPDF vs RBLD.

port url is device name.
Device name has form "com:port", or "emu:file" for virtual device.
In case of USB-COM port the "port" is the OS device name.
For example:

    "com:///\\.\COM12",
    "com:\\.\COM12",
    "com:///dev/tty/ttyACM34",
    "emu:///var/lib/ximc/virtual56.dat",
    "emu:///c:/temp/virtual56.dat",
    "emu:///c:/temp/virtual56.dat?serial=123"

Data path is path to new firmware file that need load to controller.

If we write "Old" at the end of command, the old_dev_flag will be set to 1.
if old_dev_flag == 1 using UPDF command,
else                 using RBLD command.

For using this program on Windows computers you need to place EPCboot.dll and uploader.exe in the same directory.

For build this program you need 
on Linux - go to src subdir and run commands:

    $ cmake .
    $ make
    
on Windows - use CMake-gui for Windows and create project for Microsoft Visual Studio 2012. Build this project.

Exchange with target device may be tested:
-create BOOTLOG environment variable,
-place log file path to this variable,
-start application that use library,
-read log file.

**Русский (Russian)**
Это приложение использует `urpc_firmware_update()` -- единственную функцию пользовательского API библиотеки EPCboot, 
которая внутри себя вызывает функции отправки сообщений контроллеру по алгоритму:

    сначала отсылаем rbld (или её алиас updf), чтобы перезагрузиться из основной прошивки в бутлоадер
    закрываем порт, таймаут секунды 2, открываем порт
    шлем conn, wdat, wdat, ..., wdat, disc
    rest

*Usage*: `Uploader <port url> <data path> [Old]`
Old для использования UPDF вместо RBLD.

port url - имя устройства.
Имя устройства имеет вид "com:port" или "emu:file" для виртуального устройства.
Для USB-COM устройства "port" это имя устройства в ОС.
Например:

    "com:///\\.\COM12",
    "com:\\.\COM12",
    "com:///dev/tty/ttyACM34",
    "emu:///var/lib/ximc/virtual56.dat",
    "emu:///c:/temp/virtual56.dat",
    "emu:///c:/temp/virtual56.dat?serial=123"

data path -- путь к новой прошивке
	
Если в конце команды написать Old то old_dev_flag будет установлен в 1.
если old_dev_flag = 1, то используется UPDF,
иначе                     используется RBLD.


Для использования этого приложения под Windows надо собрать EPCboot.dll, которую надо поместить в ту же директорию, что и исполняемый флаг программы.

СБОРКА программы под
под Linux - в поддиректории src запустить команды:

    $ cmake .
    $ make
    
под Windows - с помощью CMake-gui для Windows создать проект для Microsoft Visual Studio 2012. Собрать проект.

Обмен с целевым устройством использующий это приложение может быть протестирован следующим образом:
-создаём переменную окружения BOOTLOG,
-помещаем в неё путь к лог-файлу,
-запускаем программу, использующую библиотеку,
-читаем лог.


