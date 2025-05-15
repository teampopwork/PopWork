# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/vorbis/include
	${CMAKE_SOURCE_DIR}/external/openal
	${CMAKE_SOURCE_DIR}/external/ogg/include
	../
)

target_sources(${PROJECT_NAME} PRIVATE
	aureader.h
	bass.h

	bassmusicinterface.cpp
	bassmusicinterface.h
	musicinterface.cpp
	musicinterface.h
	openalsoundinterface.cpp
	openalsoundinterface.h
	openalsoundmanager.cpp
	openalsoundmanager.h
	soundinstance.h
	soundmanager.h
)