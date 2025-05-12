cmake_minimum_required(VERSION 3.18)

project(Hun-garr)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	GameApp.cpp
	Board.cpp
	TitleScreen.cpp
	OptionsDialog.cpp
	LevelupEffect.cpp
	GameOverEffect.cpp

	# Headers
	GameApp.h
	Board.h
	TitleScreen.h
	OptionsDialog.h
	LevelupEffect.h
	GameOverEffect.h
	
	../Res.h
	../Res.cpp
)

add_executable(Hun-garr ${SRC_MAIN})
add_dependencies(Hun-garr SexyAppFramework)
target_link_libraries(Hun-garr SexyAppFramework)

set_target_properties(Hun-garr
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "Hun-garr"
    RUNTIME_OUTPUT_NAME_DEBUG "Hun-garr_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "Hun-garr"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "Hun-garr_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "Hun-garr_RelWithDebugInfo"
)
