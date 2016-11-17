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
If old_dev_flag == 1 using UPDF command,
else                 using RBLD command.


For build this program you need 
on Linux - go to src subdir and run commands:

    $ cmake .
    $ make
    
on Windows - use CMake-gui for Windows and create project for Microsoft Visual Studio 2013.
Open the project.
Correct project properties:

`PROJECT-> EPCbootloaderProperties-> Configurations Properties-> Linker-> General-> Additional Library Directories`

add the path $ (SolutionDir) Debug to debug (Debug) Build Project option.
Start the building. The building will fail:

`Error 1 error LNK1181: can not open input file 'EPCboot.lib' LINK EPCbootLoader`

Repeat the building, it succeeds.

For the working (Release) version of the draft building - in

`PROJECT-> EPCbootloaderProperties-> Configurations Properties-> Linker-> General-> Additional Library Directories`

add the path $ (SolutionDir) Release.
Start the building. The building will fail:

`Error 1 error LNK1181: can not open input file 'EPCboot.lib' LINK EPCbootLoader`

Repeat the building, it succeeds.

*For using this program on Windows computers you need copy `EPCboot-master/result/Debug` or `EPCboot-master/result/Release` to you target directory and lounch `EPCbootLoader.exe` .*

Exchange with target device may be tested:
- create BOOTLOG environment variable,
- place log file path to this variable,
- start application that use library,
- read log file.

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
Если old_dev_flag = 1, то используется UPDF,
иначе                     используется RBLD.


СБОРКА программы под
под Linux - в поддиректории src запустить команды:

    $ cmake .
    $ make
    
под Windows - с помощью CMake-gui для Windows создать проект для Microsoft Visual Studio 2013. 
Открыть проект.
Поправить свойства проекта:

`PROJECT->EPCbootloaderProperties->Configurations Properties->Linker->General->Additional Library Directories` 

добавить путь $(SolutionDir)Debug в отладочный (Debug) вариант сборки проекта. 
Запустить сборку. Сборка завршится с ошибкой:

`Error	1	error LNK1181: cannot open input file 'EPCboot.lib'	LINK	EPCbootLoader`

Повторить сборку, она завершится успешно.

Для рабочего (Release) варианта сборки проекта -- в 

`PROJECT->EPCbootloaderProperties->Configurations Properties->Linker->General->Additional Library Directories`

добавить путь $(SolutionDir)Release.
Запустить сборку. Сборка завршится с ошибкой:
`Error	1	error LNK1181: cannot open input file 'EPCboot.lib'	LINK	EPCbootLoader`.
Повторить сборку, она завершится успешно.

*Для использования этого приложения под Windows надо скопировать в целевую директорию директорию `EPCboot-master/result/Debug` или директорию `EPCboot-master/result/Release`, и запускать `EPCbootLoader.exe`.*

Обмен с целевым устройством использующий это приложение может быть протестирован следующим образом:
- создаём переменную окружения BOOTLOG,
- помещаем в неё путь к лог-файлу,
- запускаем программу, использующую библиотеку,
- читаем лог.


