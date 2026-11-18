cmake_minimum_required(VERSION 3.8)
project(ASCIIART)

set(CMAKE_CXX_STANDARD 20)

set(OUTPUT_DIR ${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./bin/${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./bin/${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/${OUTPUT_DIR})

file(GLOB_RECURSE SOURCE src/**.cpp src/**.h)

add_executable(ASCIIART ${SOURCE})

target_link_directories(ASCIIART PRIVATE src)

if (WIN32)
    message(TRACE "Windows Platform")
    target_compile_definitions(ASCIIART PRIVATE
        PLATFORM_WINDOWS
    )
elseif (APPLE)
    message(TRACE "Apple Platform")
    target_compile_definitions(ASCIIART PRIVATE
        PLATFORM_APPLE
    )
elseif (UNIX)
    message(TRACE "Linux Platform")
    target_compile_definitions(ASCIIART PRIVATE
        PLATFORM_LINUX
    )
endif ()

