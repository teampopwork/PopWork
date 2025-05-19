# CMakeLists.txt
foreach(dir demo1 demo2 demo3 demo4 demo5 hun-garr v12demo v14demo xmldemo)
    add_subdirectory(src/${dir})
endforeach()

# installing and stuff
if (WIN32)
    set(BASS_PATH "${BASS_LIB_PATH}/bass.dll")
elseif (UNIX)
    set(BASS_PATH "${BASS_LIB_PATH}/libbass.so")
endif()

install(FILES
    ${BASS_PATH}
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

# pdb files
if(MSVC)
    install(FILES
        $<TARGET_PDB_FILE:Demo1>
        $<TARGET_PDB_FILE:Demo2>
        $<TARGET_PDB_FILE:Demo3>
        $<TARGET_PDB_FILE:Demo4>
        $<TARGET_PDB_FILE:Demo5>
        $<TARGET_PDB_FILE:Hun-garr>
        $<TARGET_PDB_FILE:V12Demo>
        $<TARGET_PDB_FILE:V14Demo>
        $<TARGET_PDB_FILE:XMLDemo>
        DESTINATION ${CMAKE_SOURCE_DIR}/examples/bin
        OPTIONAL
    )
endif()