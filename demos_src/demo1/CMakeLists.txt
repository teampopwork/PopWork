# CMakeLists.txt
project(Demo1)

set(SOURCES
	# Sources
	main.cpp
	gameapp.cpp
	board.cpp

	# Headers
	gameapp.h
	board.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	../
	../../
	../../PopWork/ # common.h
)

target_link_libraries(${PROJECT_NAME} PopWork)
