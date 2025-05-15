cmake_minimum_required(VERSION 3.18)

project(XMLDemo)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	XMLDemoApp.cpp
	Board.cpp

	# Headers
	XMLDemoApp.h
	Board.h
	
	../Res.h
	../Res.cpp
)

add_executable(XMLDemo ${SRC_MAIN})
add_dependencies(XMLDemo SexyAppFramework)
target_link_libraries(XMLDemo SexyAppFramework)
