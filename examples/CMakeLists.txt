# CMakeLists.txt
foreach(dir demo1 demo2 demo3 demo4 demo5 hun-garr v12demo v14demo xmldemo)
    add_subdirectory(src/${dir})
endforeach()

# installing and stuff
install(FILES
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE:OpenAL::OpenAL>
    $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
    $<TARGET_FILE:Vorbis::vorbisfile>
    $<TARGET_FILE:Vorbis::vorbis>
    ${BASS_LIB_PATH}/bass.dll
    DESTINATION ${CMAKE_SOURCE_DIR}/examples/bin
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
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/examples/bin
)
