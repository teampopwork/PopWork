cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SexyAppFramework LANGUAGES C CXX ASM VERSION 1.4.0)

set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED ON)

#setup libary paths:

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message (STATUS "Getting the x64 BASS path")
	set(BASS_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/Bass/x64)
else ()
    message (STATUS "Getting the x86 BASS path")
	set(BASS_LIB_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/lib/Bass/x86)
endif()

set(OPENAL_DLL_PATH "${CMAKE_BINARY_DIR}/_deps/openal-build/OpenAL32.dll")


set(SDL3_DLL_PATH "${CMAKE_BINARY_DIR}/_deps/sdl3-build/SDL3.dll")


add_subdirectory(source)
