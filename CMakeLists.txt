# This CMakeLists file supports two types of build modes. Either for testing or for just building the library

cmake_minimum_required(VERSION 3.14)

project(
    epaperlib
    VERSION 1.0.0
    DESCRIPTION "Library for displaying GUI on Waveshare's e-paper display."
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

if(NOT DEFINED EPAPERLIB_ENABLED_SDL_TEST_MODE)
    message(
        "TIP! Set EPAPERLIB_ENABLED_SDL_TEST_MODE to TRUE to build files in sdl_testing/"
    )
endif()

if(EPAPERLIB_STATIC)
    message("EPAPERLIB_STATIC = \"${EPAPERLIB_STATIC}\", Building epaperlib as a STATIC library")

    add_library(epaperlib STATIC lib/epaperlib.cpp)
    target_include_directories(epaperlib PUBLIC include)

else()
    message("EPAPERLIB_STATIC = \"${EPAPERLIB_STATIC}\", Building epaperlib as a SHARED library")

    add_library(epaperlib SHARED lib/epaperlib.cpp)
    target_include_directories(epaperlib PUBLIC include)
endif()

if(EPAPERLIB_ENABLED_SDL_TEST_MODE)
    message("EPAPERLIB_ENABLED_SDL_TEST_MODE = \"${EPAPERLIB_ENABLED_SDL_TEST_MODE}\",
    Building SDL test files")

    add_executable(
        sdl_test
        sdl_testing/main.cpp
    )

    target_link_libraries(sdl_test PRIVATE epaperlib)
endif()