cmake_minimum_required(VERSION 3.18)

project(Demo5)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	GameApp.cpp
	Board.cpp
	TitleScreen.cpp
	DemoDialog.cpp

	# Headers
	GameApp.h
	Board.h
	TitleScreen.h
	DemoDialog.h
	
	../Res.h
	../Res.cpp
)

add_executable(Demo5 ${SRC_MAIN})
add_dependencies(Demo5 SexyAppFramework)
target_link_libraries(Demo5 SexyAppFramework)

set_target_properties(Demo5
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "Demo5"
    RUNTIME_OUTPUT_NAME_DEBUG "Demo5_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "Demo5"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "Demo5_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "Demo5_RelWithDebugInfo"
)
