# CMakeLists.txt
project(V12Demo)

set(SOURCES
	# Sources
	main.cpp
	v12demoapp.cpp
	board.cpp
	demowidget.cpp

	# Headers
	v12demoapp.hpp
	board.hpp
	demowidget.hpp
	
	../res.hpp
	../res.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	../
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/PopWork/ # common.hpp
)

target_link_libraries(${PROJECT_NAME} PopWork)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/examples/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/examples/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/examples/bin"
    RUNTIME_OUTPUT_NAME ${PROJECT_NAME}
)

include(${CMAKE_SOURCE_DIR}/cmake/CopyDLLPost.cmake)
copy_dll_post(${PROJECT_NAME} ${BASS_PATH})