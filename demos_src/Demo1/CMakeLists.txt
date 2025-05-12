cmake_minimum_required(VERSION 3.18)

project(Demo1)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	GameApp.cpp
	Board.cpp

	# Headers
	GameApp.h
	Board.h
)

add_executable(Demo1 ${SRC_MAIN})
add_dependencies(Demo1 SexyAppFramework)
target_link_libraries(Demo1 SexyAppFramework)

set_target_properties(Demo1
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "Demo1"
    RUNTIME_OUTPUT_NAME_DEBUG "Demo1_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "Demo1"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "Demo1_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "Demo1_RelWithDebugInfo"
)
