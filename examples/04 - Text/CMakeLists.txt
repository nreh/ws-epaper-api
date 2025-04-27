add_executable(example_04_text 04_text.cpp)
target_link_libraries(example_04_text PRIVATE ws-epaper-api)

if(TARGET SDL2::SDL2)
    target_link_libraries(example_04_text PRIVATE SDL2::SDL2)
else()
    target_link_libraries(example_04_text PRIVATE SDL2)
endif()