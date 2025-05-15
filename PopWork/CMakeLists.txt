# CMakeLists.txt
cmake_minimum_required(VERSION 3.18)

project(PopWork)
add_library(PopWork STATIC)

target_sources(PopWork PRIVATE
	appbase.cpp
	appbase.h
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

set(PopWorkAppLibs
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

target_link_libraries(PopWork PUBLIC ${PopWorkAppLibs})