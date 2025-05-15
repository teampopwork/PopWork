# CMakeLists.txt
cmake_minimum_required(VERSION 3.18)

project(SexyAppFramework)

set(PROJECT_NAME SexyAppFramework)

add_library(SexyAppFramework STATIC)

target_sources(SexyAppFramework PRIVATE
	sexyappbase.cpp
	sexyappbase.h
	common.cpp
	common.h
)

# subdirectories
add_subdirectory(graphics)
add_subdirectory(audio)
add_subdirectory(math)
add_subdirectory(debug)
add_subdirectory(misc)
add_subdirectory(readwrite)
add_subdirectory(resources)
add_subdirectory(widget)
add_subdirectory(imagelib)
add_subdirectory(paklib)

set(SexyAppLibs
	SDL3::SDL3
	SDL3_ttf::SDL3_ttf
	OpenAL::OpenAL
	miniaudio
	ogg
	Vorbis::vorbisfile
	Vorbis::vorbis
	winmm
	ws2_32
	${BASS_LIB_PATH}/bass.lib
)

target_link_libraries(SexyAppFramework PUBLIC ${SexyAppLibs})