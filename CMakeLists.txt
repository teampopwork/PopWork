# CMakeLists.txt
cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SexyAppFramework LANGUAGES C CXX ASM VERSION 1.4.0)

set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED ON)

# temp workaround for me
set(_Python3_EXECUTABLE_DEBUG "" CACHE FILEPATH "Python debug executable")

option(USE_WIDESTRING "Wide Strings" ON)
option(BUILD_DEMOS "Build Demos" ON)
option(CONSOLE "Show the console on Windows" ON)

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

set(OPENAL_DLL_PATH "${CMAKE_BINARY_DIR}/_deps/openal-build/OpenAL32.dll")

set(SDL3_DLL_PATH "${CMAKE_BINARY_DIR}/_deps/sdl3-build/SDL3.dll")

# external libraries
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build as DLL" FORCE)

# chatgpt suggested this idk if this works
set(INSTALL_VORBIS OFF CACHE BOOL "" FORCE)
set(INSTALL_OGG OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDLTTF_INSTALL OFF CACHE BOOL "" FORCE)
set(OPENAL_INSTALL OFF CACHE BOOL "" FORCE)
set(MINIAUDIO_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/ogg EXCLUDE_FROM_ALL)
add_subdirectory(external/vorbis EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(external/openal EXCLUDE_FROM_ALL)
add_subdirectory(external/miniaudio EXCLUDE_FROM_ALL)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as DLL" FORCE)

add_subdirectory(SexyAppFramework)

if (BUILD_DEMOS)
	add_subdirectory(demos_src)
endif()
