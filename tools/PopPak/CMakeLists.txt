# CMakeLists.txt
project(PopPak)

set(SOURCES
	# Sources
	poppak.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
	../../PopWork
    ../../PopWork/paklib
)

target_link_libraries(${PROJECT_NAME} PopWork)

install(TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/tools
)
