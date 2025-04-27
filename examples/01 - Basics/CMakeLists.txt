add_executable(example_01_basics 01_basics.cpp)
target_link_libraries(example_01_basics PRIVATE ws-epaper-api)

if(TARGET SDL2::SDL2)
    target_link_libraries(example_01_basics PRIVATE SDL2::SDL2)
else()
    target_link_libraries(example_01_basics PRIVATE SDL2)
endif()