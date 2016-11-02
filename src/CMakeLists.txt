cmake_minimum_required(VERSION 2.8)
 
project(EPCbootLoader C)

if(CMAKE_VERSION VERSION_LESS "3.1")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set (CMAKE_C_FLAGS "--std=gnu99 ${CMAKE_C_FLAGS}")
    endif()
else()
    set(CMAKE_C_STANDARD 99)
endif()

add_definitions(-DURPC_EXPORTS)

include_directories(../srclib)

add_executable(EPCbootLoader main.c) 

if(WIN32)
  target_link_libraries(EPCbootLoader EPCboot.lib)
else()
  target_link_libraries(EPCbootLoader EPCboot)
endif()
  
  