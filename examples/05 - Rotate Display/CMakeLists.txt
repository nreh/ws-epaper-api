add_executable(example_05_rotate_display 05_rotate_display.cpp)
target_link_libraries(example_05_rotate_display PRIVATE ws-epaper-api)

if(TARGET SDL2::SDL2)
    target_link_libraries(example_05_rotate_display PRIVATE SDL2::SDL2)
else()
    target_link_libraries(example_05_rotate_display PRIVATE SDL2)
endif()