# CMakeLists.txt
cmake_minimum_required(VERSION 4.0.2 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PopWork LANGUAGES C CXX ASM VERSION 1.4.0)

set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED ON)

# temp workaround for me
set(_Python3_EXECUTABLE_DEBUG "" CACHE FILEPATH "Python debug executable")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(USE_WIDESTRING "Wide Strings" ON)
option(BUILD_DEMOS "Build Demos" ON)
option(CONSOLE "Show the console on Windows" ON)
option(BUILD_TOOLS "Build Tools" ON)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Using x64")
	set(IS_64BIT true)
else ()
    message (STATUS "Using x86")
	set(IS_64BIT false)
endif()

if(USE_WIDESTRING)
	add_compile_definitions(_USE_WIDE_STRING)
endif()

if (IS_64BIT)
    message (STATUS "Getting the x64 BASS path")
	set(BASS_LIB_PATH ${CMAKE_SOURCE_DIR}/lib/Bass/x64)
	message (${BASS_LIB_PATH})
else ()
    message (STATUS "Getting the x86 BASS path")
	set(BASS_LIB_PATH  ${CMAKE_SOURCE_DIR}/lib/Bass/x86)
	message (${BASS_LIB_PATH})
endif()

# external libraries
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as DLL" FORCE)
add_subdirectory(external/ogg EXCLUDE_FROM_ALL)
add_subdirectory(external/vorbis EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(external/openal EXCLUDE_FROM_ALL)
add_subdirectory(external/miniaudio EXCLUDE_FROM_ALL)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as DLL" FORCE)

add_subdirectory(PopWork)
if(BUILD_TOOLS AND WIN32) # we can't afford linux yet
add_subdirectory(tools/PopPak)
add_subdirectory(tools/PopPakPWE)
endif()

if (BUILD_DEMOS)
	add_subdirectory(demos_src)
endif()
