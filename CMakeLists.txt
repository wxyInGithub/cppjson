cmake_minimum_required(VERSION 3.15)

project(cppjson
    VERSION 0.1.0
    DESCRIPTION "A small JSON library written in C++"
    LANGUAGES CXX)

# global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ---------- source files ----------
add_library(cppjson STATIC
    src/array.cpp
    src/object.cpp
    src/jsonValue.cpp
    src/print.cpp
    src/parser.cpp)

# offer api
add_library(cppjson::cppjson ALIAS cppjson)

target_include_directories(cppjson
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

if(MSVC)
    target_compile_options(cppjson PRIVATE /W4 /utf-8)
else()
    target_compile_options(cppjson PRIVATE -Wall -Wextra)
endif()

# Only when debuging this library can the exe generated under ./example
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

    # set the dir where the executive file is generated
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples")
    # Delete the child dir IDE generated for DEBUG/RELEASE
    foreach(_cfg IN ITEMS DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_cfg} "${CMAKE_CURRENT_SOURCE_DIR}/examples")
    endforeach()

    # Put the static lib to build/
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

    # ---------- generate exe for test ----------
    add_executable(test examples/test.cpp)
    target_link_libraries(test PRIVATE cppjson::cppjson)

    # ensure that test exe is generated under examples/
    set_target_properties(test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/examples")

endif()