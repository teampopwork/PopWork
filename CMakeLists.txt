cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SexyAppFramework LANGUAGES C CXX ASM VERSION 1.4.0)

set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED ON)

function(copyDlls)
    get_target_property(output_dir ${PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)
    file(COPY ${SDL3_DLL_PATH} DESTINATION ${output_dir})
    file(COPY ${OPENAL_DLL_PATH} DESTINATION ${output_dir})
    file(COPY ${BASS_LIB_PATH}/bass.dll DESTINATION ${output_dir})
    message("Copied the DLLs into build folder.")
endfunction()

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

option(BuildDemos "Build Demos" ON)

option(CONSOLE "Show console on Windows" ON)


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

include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        # This will be a tag once SDL3 is released
        GIT_TAG origin/main
    )
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
        SDL_TTF
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
        # This will be a tag once SDL3 is released
        GIT_TAG origin/main
    )
FetchContent_MakeAvailable(SDL_TTF)

FetchContent_Declare(
    openAL
    GIT_REPOSITORY https://github.com/kcat/openal-soft
    GIT_TAG        master
)

FetchContent_MakeAvailable(openAL)

FetchContent_Declare(
    miniAudio
    GIT_REPOSITORY https://github.com/mackron/miniaudio
    GIT_TAG        master
)

FetchContent_MakeAvailable(miniAudio)

add_subdirectory(SexyAppFramework)

if (${BuildDemos})
	add_subdirectory(demos_src)
endif()
