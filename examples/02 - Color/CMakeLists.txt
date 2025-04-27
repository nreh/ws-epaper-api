add_executable(example_02_color 02_color.cpp)
target_link_libraries(example_02_color PRIVATE ws-epaper-api)

if(TARGET SDL2::SDL2)
    target_link_libraries(example_02_color PRIVATE SDL2::SDL2)
else()
    target_link_libraries(example_02_color PRIVATE SDL2)
endif()