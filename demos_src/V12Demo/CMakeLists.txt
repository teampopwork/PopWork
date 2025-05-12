cmake_minimum_required(VERSION 3.18)

project(V12Demo)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	V12DemoApp.cpp
	Board.cpp
	DemoWidget.cpp

	# Headers
	V12DemoApp.h
	Board.h
	DemoWidget.h
	
	../Res.h
	../Res.cpp
)

add_executable(V12Demo ${SRC_MAIN})
add_dependencies(V12Demo SexyAppFramework)
target_link_libraries(V12Demo SexyAppFramework)

set_target_properties(V12Demo
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "V12Demo"
    RUNTIME_OUTPUT_NAME_DEBUG "V12Demo_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "V12Demo"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "V12Demo_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "V12Demo_RelWithDebugInfo"
)
