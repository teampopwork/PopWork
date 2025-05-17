# CMakeLists.txt
project(V14Demo)

set(SOURCES
	# Sources
	main.cpp
	v14demoapp.cpp
	board.cpp
	demowidget.cpp

	# Headers
	v14demoapp.h
	board.h
	demowidget.h
	
	../res.h
	../res.cpp
)

if(WIN32)
    list(APPEND SOURCES resources.rc)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	../
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/PopWork/ # common.h
)

target_link_libraries(${PROJECT_NAME} PopWork)
