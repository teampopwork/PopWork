cmake_minimum_required(VERSION 3.18)

project(Demo3)

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

add_executable(Demo3 ${SRC_MAIN})
add_dependencies(Demo3 SexyAppFramework)
target_link_libraries(Demo3 SexyAppFramework)

set_target_properties(Demo3
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "Demo3"
    RUNTIME_OUTPUT_NAME_DEBUG "Demo3_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "Demo3"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "Demo3_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "Demo3_RelWithDebugInfo"
)
