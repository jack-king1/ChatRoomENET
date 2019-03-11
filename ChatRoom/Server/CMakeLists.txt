project(Server)

## out of source builds ##
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin")

## set to true to use dlls instead of static libs ##
option(STATIC_APP "Build a static application" ON)
if( STATIC_APP )
    message("##### BUILDING STATIC APPLICATION #####")
    set(BUILD_SHARED_LIBS false)
else()
    message("##### BUILDING SHARED APPLICATION #####")
    set(BUILD_SHARED_LIBS true)
endif()

## the application output ##
add_executable(
        ${PROJECT_NAME}
        Source/main.cpp
        Source/Server.h
        Source/Server.cpp
        ${CMAKE_SOURCE_DIR}/Shared/Include/ChatMsg.h
        ${CMAKE_SOURCE_DIR}/Shared/Include/Printer.h
        ${CMAKE_SOURCE_DIR}/Shared/Source/Printer.cpp
        ${CMAKE_SOURCE_DIR}/Shared/Source/ChatMsg.cpp )

## utility scripts
include(${CMAKE_SOURCE_DIR}/CMake/compilation.cmake)