cmake_minimum_required(VERSION 3.14)

project (IPEP)

set (TARGET_NAME )

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()

add_subdirectory(Device)
