**English**
The aim of this programm is loading firmware to UltraRay XIMC controllers.

*Usage*: `Uploader <port url> <data path> [Old]`

*port url* is device name.
Device name has form "com:port", or "emu:file" for virtual device.
In case of USB-COM port the "port" is the OS device name.
For example:

    "com:///\\.\COM12",
    "com:\\.\COM12",
    "com:///dev/tty/ttyACM34",
    "emu:///var/lib/ximc/virtual56.dat",
    "emu:///c:/temp/virtual56.dat",
    "emu:///c:/temp/virtual56.dat?serial=123"

*data path* is path to new firmware file that need load to controller.

*Old* for using UPDF on old controller versions vs RBLD on new.

For build this program you need 
**on Linux** - go to src subdir and run commands:

    $ cmake .
    $ make
    
**on Windows** - use CMake-gui for Windows and create project for Microsoft Visual Studio 2013.
(https://www.johnlamp.net/cmake-tutorial-3-gui-tool.html)

Open the project. Select some debugging or release version of the project we will build.

Build the library: go to subproject EPCboot and build it.

Go to EPCbootLoader. Correct project properties:

`PROJECT-> EPCbootloaderProperties-> Configurations Properties-> Linker-> General-> Additional Library Directories`

and add the path $(TargetDir).
Build. 

Exchange with target device may be tested:
- create BOOTLOG environment variable,
- place log file path to this variable,
- start application that use library,
- read log file.

**Русский (Russian)**
Это приложение предназначено для того, чтобы заливать прошивки в контроллеры UltraRay XIMC.

*Использование*: `EPCBootLoader <port url> <data path> [Old]`

*port url* - имя устройства.
Имя устройства имеет вид "com:port" или "emu:file" для виртуального устройства.
Для USB-COM устройства "port" это имя устройства в ОС.
Например:

    "com:///\\.\COM12",
    "com:\\.\COM12",
    "com:///dev/tty/ttyACM34",
    "emu:///var/lib/ximc/virtual56.dat",
    "emu:///c:/temp/virtual56.dat",
    "emu:///c:/temp/virtual56.dat?serial=123"

*data path* -- путь к новой прошивке.

*Old* добавляется для старых устройств, использующих команду UPDF вместо RBLD.

СБОРКА программы 
**под Linux** - в поддиректории src запустить команды:

    $ cmake .
    $ make
    
**под Windows** - с помощью CMake-gui для Windows создать проект для Microsoft Visual Studio 2013. 
(см. https://www.johnlamp.net/cmake-tutorial-3-gui-tool.html)

Открыть проект. Выбрать какую, отладочную (Debug) или основную (Release) версию проекта мы будем собирать.

Собрать библиотеку: перейти к подпроекту EPCBoot и собрать его.

Перейти к подпроекту EPCBootLoader. Поправить свойства проекта:

`PROJECT->EPCbootLoaderProperties->Configurations Properties->Linker->General->Additional Library Directories` 

добавить путь $(TargetDir). Собрать.

Обмен с целевым устройством, использующий это приложение, может быть протестирован следующим образом:
- создаём переменную окружения BOOTLOG,
- помещаем в неё путь к лог-файлу,
- запускаем программу, использующую библиотеку,
- читаем лог.


