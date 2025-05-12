cmake_minimum_required(VERSION 3.18)

project(Demo2)

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

add_executable(Demo2 ${SRC_MAIN})
add_dependencies(Demo2 SexyAppFramework)
target_link_libraries(Demo2 SexyAppFramework)

set_target_properties(Demo2
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "Demo2"
    RUNTIME_OUTPUT_NAME_DEBUG "Demo2_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "Demo2"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "Demo2_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "Demo2_RelWithDebugInfo"
)
