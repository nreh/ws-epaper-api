function(create_example_target target filename)
    add_executable(${target} ${filename})
    target_link_libraries(${target} PRIVATE ws-epaper-api)

    if(TARGET SDL2::SDL2)
        target_link_libraries(${target} PRIVATE SDL2::SDL2)
    else()
        target_link_libraries(${target} PRIVATE SDL2)
    endif()

    if(WIN32)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${target}> $<TARGET_RUNTIME_DLLS:${target}>
            COMMAND_EXPAND_LISTS
        )
    endif()
endfunction()

add_subdirectory("01 - Basics")
add_subdirectory("02 - Color")
add_subdirectory("03 - Emulating Physical Displays")
add_subdirectory("04 - Text")
add_subdirectory("05 - Rotate Display")
add_subdirectory("06 - Drawing Images")
add_subdirectory("07 - Real World Example")
add_subdirectory("08 - Element Showcase")
add_subdirectory("09 - Custom Elements")
add_subdirectory("10 - Canvas Element")