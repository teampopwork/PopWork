# CMakeLists.txt
project(Demo5)

set(SOURCES
	# Sources
	main.cpp
	gameapp.cpp
	board.cpp
	titlescreen.cpp
	demodialog.cpp

	# Headers
	gameapp.h
	board.h
	titlescreen.h
	demodialog.h
	
	../res.h
	../res.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	../
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/PopWork/ # common.h
)

target_link_libraries(${PROJECT_NAME} PopWork)
