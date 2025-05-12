cmake_minimum_required(VERSION 3.18)

project(Demo4)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	GameApp.cpp
	Board.cpp
	TitleScreen.cpp

	# Headers
	GameApp.h
	Board.h
	TitleScreen.h
	
	../Res.h
	../Res.cpp
)

add_executable(Demo4 ${SRC_MAIN})
add_dependencies(Demo4 SexyAppFramework)
target_link_libraries(Demo4 SexyAppFramework)

set_target_properties(Demo4
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "Demo4"
    RUNTIME_OUTPUT_NAME_DEBUG "Demo4_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "Demo4"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "Demo4_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "Demo4_RelWithDebugInfo"
)
