cmake_minimum_required(VERSION 2.8)
 
project(epcbootlib C)

if(CMAKE_VERSION VERSION_LESS "3.1")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set (CMAKE_C_FLAGS "--std=gnu99 ${CMAKE_C_FLAGS}")
    endif()
else()
    set(CMAKE_C_STANDARD 99)
endif()

add_definitions(-DURPC_EXPORTS)
 
set(HEADERS
    common.h
    metadata.h
    platform.h
    protosup.h
    sglib.h
    types.h
    util.h
    bootloader.h
    atomicrun.h
    settings.h

    commands.h
    iobuffer.h
    flowparser.h
    algorithm.h
    macro.h
    handlers.h
    api.h
    aes.h
)

set(SOURCES
    protosup.c
    util.c
    bootloader.c
    devvirt.c

    commands.c
    iobuffer.c
    flowparser.c
    algorithm.c
    handlers.c
    api.c
    aes.c
    encrypt_key.c
)

IF(WIN32)
set(SOURCES
    ${SOURCES}
    platform-win32.c
)
ELSE()
set(SOURCES
    ${SOURCES}
    platform-posix.c
)
ENDIF()


add_library (epcbootlib SHARED ${HEADERS} ${SOURCES})

if(WIN32)
  target_link_libraries(epcbootlib SetupAPI.lib)
else()
  target_link_libraries(epcbootlib pthread)
endif()


project (epcboot, C)

add_executable(epcboot main.c)

if(WIN32)
  target_link_libraries(epcboot epcbootlib.lib)
else()
  target_link_libraries(epcboot epcbootlib
          )
endif()