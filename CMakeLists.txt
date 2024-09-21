cmake_minimum_required(VERSION 3.14)

project(
    epaperapi
    VERSION 1.0.0
    DESCRIPTION "Library that provides an abstraction layer for displaying GUI on Waveshare's e-paper display."
    LANGUAGES C CXX
)

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR
        "IN-SOURCE BUILD NOT ALLOWED!\n"
        "You're not allowed to build in this folder."
        " Please create a separate build subdirectory and run 'cmake ..' from there.\n"
        "If you're unsure what this means, follow the steps for building in the README exactly.\n"
        "Also, you should delete the newly created 'CMakeCache.txt' file and 'CMakeFiles/' directory that were just created."
    )
endif()

if(NOT DEFINED EPAPERAPI_ENABLED_SDL_TEST_MODE)
    message(
        "TIP! Set EPAPERAPI_ENABLED_SDL_TEST_MODE to TRUE to build files in sdl_testing/"
    )
endif()

add_subdirectory(external/bcm2835)
add_subdirectory(external/waveshare/epaper)

if(EPAPERAPI_STATIC)
    message("EPAPERAPI_STATIC = \"${EPAPERAPI_STATIC}\", Building EPAPERAPI as a STATIC library")

    add_library(epaperapi STATIC lib/epaperapi.cpp)
    target_include_directories(epaperapi PUBLIC include)

else()
    message("EPAPERAPI_STATIC = \"${EPAPERAPI_STATIC}\", Building EPAPERAPI as a SHARED library")

    add_library(epaperapi SHARED lib/epaperapi.cpp)
    target_include_directories(epaperapi PUBLIC include)
endif()

target_link_libraries(epaperapi PRIVATE bcm2835)

if(EPAPERAPI_ENABLED_SDL_TEST_MODE)
    message("EPAPERAPI_ENABLED_SDL_TEST_MODE = \"${EPAPERAPI_ENABLED_SDL_TEST_MODE}\", Building SDL test files")

    add_executable(
        sdl_test
        sdl_testing/main.cpp
    )

    target_link_libraries(sdl_test PRIVATE epaperapi)
endif()