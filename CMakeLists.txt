# CMakeLists.txt
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PopWork LANGUAGES C CXX ASM VERSION 1.4.0)

set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED ON)

# temp workaround for me
set(_Python3_EXECUTABLE_DEBUG "" CACHE FILEPATH "Python debug executable")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(USE_WIDESTRING "Wide Strings" ON)
option(BUILD_EXAMPLES "Build Examples" ON)
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

if(CONSOLE AND WIN32)
	add_compile_definitions(_CONSOLE_ON)
endif()

if (IS_64BIT)
    message (STATUS "Getting the x64 BASS path")
	set(BASS_LIB_PATH ${CMAKE_SOURCE_DIR}/lib/bass/x64)
	message (${BASS_LIB_PATH})
else ()
    message (STATUS "Getting the x86 BASS path")
	set(BASS_LIB_PATH  ${CMAKE_SOURCE_DIR}/lib/bass/x86)
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

if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

include_directories(
  /usr/include/c++/12
  /usr/include/x86_64-linux-gnu/c++/12
  /usr/include/c++/12/backward
  /usr/lib/gcc/x86_64-linux-gnu/12/include
  /usr/local/include
  /usr/include/x86_64-linux-gnu
  /usr/include
)

# djugjsfgufdgujdfgiujgdijfgifjdgidfjgifdgjfdgufdguifdg electr0gunner told me to add this
if(BUILD_DEMOS OR BUILD_TOOLS)
    set(demo_deps PopWork)

    if(BUILD_DEMOS)
        list(APPEND demo_deps
            Demo1 Demo2 Demo3 Demo4 Demo5
            Hun-garr V12Demo V14Demo XMLDemo
        )
    endif()

    if(BUILD_DEMOS AND BUILD_TOOLS AND WIN32)
        list(APPEND demo_deps PopPak PopPakPWE)
    endif()

    add_custom_target(alldemos ALL DEPENDS ${demo_deps})
endif()

if(NOT (DEFINED ENV{GITHUB_ACTIONS} AND "$ENV{GITHUB_ACTIONS}" STREQUAL "true"))
    add_custom_command(TARGET alldemos POST_BUILD
        COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --config $<CONFIG>
    )
endif()