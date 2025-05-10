cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SexyAppFramework LANGUAGES C CXX ASM VERSION 1.4.0)

set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED ON)

#setup libaries:
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