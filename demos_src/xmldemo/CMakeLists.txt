# CMakeLists.txt
project(XMLDemo)

set(SOURCES
	# Sources
	main.cpp
	xmldemoapp.cpp
	board.cpp

	# Headers
	xmldemoapp.h
	board.h
	
	../res.h
	../res.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	../
	../../
)

target_link_libraries(${PROJECT_NAME} PopWork)
