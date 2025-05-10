cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SexyAppFramework LANGUAGES C CXX ASM VERSION 1.4.0)

set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED ON)

#setup libaries:


set(ZLIB_BUILD_TESTING OFF CACHE BOOL "Enable Zlib Examples as tests" FORCE)
set(ZLIB_INSTALL OFF CACHE BOOL "Enable installation of zlib" FORCE)

set(PNG_SHARED ON CACHE BOOL "" FORCE)
set(PNG_STATIC OFF CACHE BOOL "" FORCE)
set(PNG_EXECUTABLES OFF CACHE BOOL "" FORCE)
set(PNG_TESTS OFF CACHE BOOL "" FORCE)
set(PNG_TOOLS OFF CACHE BOOL "" FORCE)
set(SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)

add_subdirectory(lib/zlib EXCLUDE_FROM_ALL)
set(ZLIB_ROOT lib/zlib)
set(ZLIB_LIBRARY ZLIB::ZLIB)
set(ZLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/zlib")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message (STATUS "Using x64")
	set(IS_64BIT true)
else ()
    message (STATUS "Using x86")
	set(IS_64BIT false)
endif()

option(WideStrings "Wide Strings" ON)
if (${WideStrings})
	add_compile_definitions(_USE_WIDE_STRING)
endif()

add_subdirectory(SexyAppFramework)

option(BuildDemos "Build Demos" ON)

option(CONSOLE "Show console on Windows" ON)

if (${BuildDemos})
	add_subdirectory(demos_src)
endif()