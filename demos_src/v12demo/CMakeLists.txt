# CMakeLists.txt
project(V12Demo)

set(SOURCES
	# Sources
	main.cpp
	v12demoapp.cpp
	board.cpp
	demowidget.cpp

	# Headers
	v12demoapp.h
	board.h
	demowidget.h
	
	../res.h
	../res.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	../
	../../
)

target_link_libraries(${PROJECT_NAME} PopWork)
