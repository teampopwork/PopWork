cmake_minimum_required(VERSION 3.18)

project(XMLDemo)

include_directories(../../)

set(SRC_MAIN
	# Sources
	main.cpp
	XMLDemoApp.cpp
	Board.cpp

	# Headers
	XMLDemoApp.h
	Board.h
	
	../Res.h
	../Res.cpp
)

add_executable(XMLDemo WIN32 ${SRC_MAIN})
add_dependencies(XMLDemo SexyAppFramework)
target_link_libraries(XMLDemo SexyAppFramework)

set_target_properties(XMLDemo
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/demos"
    RUNTIME_OUTPUT_NAME "XMLDemo"
    RUNTIME_OUTPUT_NAME_DEBUG "XMLDemo_Debug"
    RUNTIME_OUTPUT_NAME_RELEASE "XMLDemo"
    RUNTIME_OUTPUT_NAME_MINSIZEREL "XMLDemo_MinSizeRel"
    RUNTIME_OUTPUT_NAME_RELWITHDEBINFO "XMLDemo_RelWithDebugInfo"
)

add_custom_command(TARGET XMLDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${BASS_LIB_PATH}/bass.dll"
        "${CMAKE_SOURCE_DIR}/demos"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OPENAL_DLL_PATH}"
        "${CMAKE_SOURCE_DIR}/demos"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_DLL_PATH}"
        "${CMAKE_SOURCE_DIR}/demos"
    COMMAND ${CMAKE_COMMAND} -E echo "Copied the DLLs into build folder."
)