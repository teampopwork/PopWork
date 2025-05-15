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
