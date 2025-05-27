# CMakeLists.txt

# installing and stuff
if (WIN32)
    set(BASS_PATH "${BASS_LIB_PATH}/bass.dll")
elseif (UNIX)
    set(BASS_PATH "${BASS_LIB_PATH}/libbass.so")
endif()

# adding the demos
foreach(dir demo1 demo2 demo3 demo4 demo5 hun-garr v12demo v14demo xmldemo barebones)
    add_subdirectory(src/${dir})
endforeach()
