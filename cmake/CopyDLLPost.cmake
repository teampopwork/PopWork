function(copy_dll_post TARGET DLL_PATH)
    if (EXISTS "${DLL_PATH}")
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${DLL_PATH}"
                "$<TARGET_FILE_DIR:${TARGET}>"
            COMMENT "Copying runtime DLL: ${DLL_PATH} to output directory"
        )
    else()
        message(WARNING "DLL not found: ${DLL_PATH}")
    endif()
endfunction()