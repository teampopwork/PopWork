cmake_minimum_required(VERSION 3.18)

project(V14Demo)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	V14DemoApp.cpp
	Board.cpp
	DemoWidget.cpp

	# Headers
	V14DemoApp.h
	Board.h
	DemoWidget.h
	
	../Res.h
	../Res.cpp
)

add_executable(V14Demo ${SRC_MAIN})
add_dependencies(V14Demo SexyAppFramework)
target_link_libraries(V14Demo SexyAppFramework)

set_target_properties(V14Demo
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "V14Demo"
    RUNTIME_OUTPUT_NAME_DEBUG "V14Demo_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "V14Demo"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "V14Demo_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "V14Demo_RelWithDebugInfo"
)
