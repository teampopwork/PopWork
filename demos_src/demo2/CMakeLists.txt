# CMakeLists.txt
project(Demo2)

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
)

target_link_libraries(${PROJECT_NAME} PopWork)
