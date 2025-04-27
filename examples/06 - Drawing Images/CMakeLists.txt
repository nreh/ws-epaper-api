add_executable(example_06_drawing_images 06_drawing_images.cpp)
target_link_libraries(example_06_drawing_images PRIVATE ws-epaper-api)

if(TARGET SDL2::SDL2)
    target_link_libraries(example_06_drawing_images PRIVATE SDL2::SDL2)
else()
    target_link_libraries(example_06_drawing_images PRIVATE SDL2)
endif()