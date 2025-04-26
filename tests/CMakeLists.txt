add_executable(test_build build.cpp)
target_link_libraries(test_build PRIVATE ws-epaper-api)