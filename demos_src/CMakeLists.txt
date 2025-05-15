# CMakeLists.txt
cmake_minimum_required(VERSION 3.18)

add_subdirectory(Demo1)
add_subdirectory(Demo2)
add_subdirectory(Demo3)
add_subdirectory(Demo4)
add_subdirectory(Demo5)
add_subdirectory(Hun-garr)
add_subdirectory(V12Demo)
add_subdirectory(V14Demo)
add_subdirectory(XMLDemo)

# installing and stuff
install(FILES
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE:OpenAL::OpenAL>
    $<TARGET_FILE:Vorbis::vorbis>
    $<TARGET_FILE:Vorbis::vorbisfile>
    $<TARGET_FILE:ogg>
    $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
#   $<TARGET_FILE:miniaudio>
    ${BASS_LIB_PATH}/bass.dll
    DESTINATION ${CMAKE_SOURCE_DIR}/demos
)

install(TARGETS
    Demo1
    Demo2
    Demo3
    Demo4
    Demo5
    Hun-garr
    V12Demo
    V14Demo
    XMLDemo
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/demos
)