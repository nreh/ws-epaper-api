add_executable(example_03_physical_displays 03_physical_displays.cpp)
target_link_libraries(example_03_physical_displays PRIVATE ws-epaper-api)

if(TARGET SDL2::SDL2)
    target_link_libraries(example_03_physical_displays PRIVATE SDL2::SDL2)
else()
    target_link_libraries(example_03_physical_displays PRIVATE SDL2)
endif()