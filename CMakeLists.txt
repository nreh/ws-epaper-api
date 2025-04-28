cmake_minimum_required(VERSION 3.14)

project(
    ws-epaper-api
    VERSION 1.0.0
    DESCRIPTION "Library that provides an abstraction layer for displaying GUI on Waveshare's e-paper display."
    LANGUAGES C CXX
)

if(WIN32)
    # This ensures that on Windows we're generating a epaperlib.lib
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR
        "IN-SOURCE BUILD NOT ALLOWED!\n"
        "You're not allowed to build in this folder."
        " Please create a separate build subdirectory and run 'cmake ..' from there.\n"
        "If you're unsure what this means, follow the steps for building in the README exactly.\n"
        "Also, you should delete the newly created 'CMakeCache.txt' file and 'CMakeFiles/' directory that were just created."
    )
endif()

option(ENABLE_EMULATION "Build with emulation support using SDL" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(ENABLE_TESTS "Build the tests" ON)

if(NOT ENABLE_EMULATION)
    message(
        "TIP! Set ENABLE_EMULATION to ON to enable SDL emulation support"
    )
endif()

if(NOT BUILD_EXAMPLES)
    message(
        "TIP! Set BUILD_EXAMPLES to ON to build files in examples/ directory"
    )
endif()

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

set(
    EPAPER_LIB_FILES
    lib/wsepaperapi.cpp
    lib/buffers.cpp
    lib/debug.cpp
)

if(WSEPAPERAPI_STATIC)
    message("WSEPAPERAPI_STATIC = \"${WSEPAPERAPI_STATIC}\", Building ws-epaper-api as a STATIC library")
    add_library(ws-epaper-api STATIC ${EPAPER_LIB_FILES})
else()
    message("WSEPAPERAPI_STATIC = \"${WSEPAPERAPI_STATIC}\", Building ws-epaper-api as a SHARED library")
    add_library(ws-epaper-api SHARED ${EPAPER_LIB_FILES})
endif()

target_include_directories(ws-epaper-api PUBLIC include)
target_include_directories(ws-epaper-api PUBLIC emulate)

if(WIN32)
    # Certain headerfiles and libraries exist on linux but not windows, without them we can't include the bcm2835 which means
    # that cross-compilation isn't possible.
    set(WSEPAPERAPI_CROSSCOMPILATION_SUPPORT FALSE)
    message(WARNING
        "Because you're building on Windows, bcm2835 cannot be included. As a result, there will be no crosscompilation support."
        "\nYou should probably build with ENABLE_EMULATION = ON or there's really no point to building this library. "
        "Run cmake with -DENABLE_EMULATION=ON"
    )
    add_compile_definitions(WSEPAPERAPI_NO_CROSSCOMPILATION_SUPPORT TRUE)
else()
    add_subdirectory(external/bcm2835)
    add_subdirectory(external/waveshare)

    set(WSEPAPERAPI_CROSSCOMPILATION_SUPPORT TRUE)
    target_include_directories(ws-epaper-api PUBLIC external/bcm2835/src)
    target_link_libraries(epaper PUBLIC bcm2835)
    target_link_libraries(ws-epaper-api PUBLIC epaper)
endif()

target_compile_features(
    ws-epaper-api PRIVATE cxx_std_17
)

if(ENABLE_EMULATION)
    message("ENABLE_EMULATION = \"${ENABLE_EMULATION}\", Looking for SDL library...")

    find_package(SDL2)

    if(SDL2_FOUND)
        message("Found SDL library")
    else()
        message(FATAL_ERROR "SDL2 library not found! Please install SDL2 to build in SDL test mode."
            "\nOtherwise set ENABLE_EMULATION to OFF."
        )
    endif()

    # add_executable(
    # sdl_test
    # sdl_testing/main.cpp
    # )
    # TODO: REMOVE THIS
    if(WIN32)
        add_custom_command(TARGET sdl_test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:sdl_test> $<TARGET_FILE_DIR:sdl_test>
            COMMAND_EXPAND_LISTS
        )
    endif()

    # target_link_libraries(sdl_test PRIVATE ws-epaper-api)
    # if(TARGET SDL2::SDL2)
    # target_link_libraries(sdl_test PRIVATE SDL2::SDL2)
    # else()
    # target_link_libraries(sdl_test PRIVATE SDL2)
    # endif()
endif()

if(BUILD_EXAMPLES)
    message("BUILD_EXAMPLES = \"${BUILD_EXAMPLES}\", Adding ./examples directory to build...")

    if(NOT ENABLE_EMULATION)
        message(FATAL_ERROR
            "Building the examples requires emulation support! Set ENABLE_EMULATION to ON as well!"
        )
    endif()

    add_subdirectory(./examples)
endif()