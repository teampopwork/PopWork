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
add_dependencies(Demo2 PopWork)
target_link_libraries(Demo2 PopWork)
