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
