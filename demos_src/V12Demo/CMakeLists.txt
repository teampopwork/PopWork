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
