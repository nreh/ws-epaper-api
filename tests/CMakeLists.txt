add_executable(test_build all_draw_targets_build.cpp)
target_link_libraries(test_build PRIVATE ws-epaper-api)

add_test(NAME test_build COMMAND test_build)