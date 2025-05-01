cmake_minimum_required(VERSION 3.14)

project(
    ws-epaper-api
    VERSION 1.0.0
    DESCRIPTION "Library that provides an abstraction layer for displaying GUI on Waveshare's e-paper display."
    LANGUAGES C CXX
)

# *********************************************************************
# * Windows only stuff
# *********************************************************************
if(WIN32)
    # This ensures that on Windows we're generating a epaperlib.lib
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# *********************************************************************
# * Prevent in-source builds
# *********************************************************************
if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR
        "IN-SOURCE BUILD NOT ALLOWED!\n"
        "You're not allowed to build in this folder."
        " Please create a separate build subdirectory and run 'cmake ..' from there.\n"
        "If you're unsure what this means, follow the steps for building in the README exactly.\n"
        "Also, you should delete the newly created 'CMakeCache.txt' file and 'CMakeFiles/' directory that were just created."
    )
endif()

# *********************************************************************
# * Options
# *********************************************************************
option(ENABLE_EMULATION "Build with emulation support using SDL" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(ENABLE_TESTS "Build the tests" OFF)
option(WSEPAPERAPI_STATIC "Build the library in static mode" OFF)

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
    message("ENABLE_TESTS = \"${ENABLE_TESTS}\", Building tests")
    enable_testing()
    add_subdirectory(tests)
endif()

# *********************************************************************
# * Add all source files
# *********************************************************************
set(
    EPAPER_LIB_FILES
    lib/wsepaperapi.cpp
    lib/buffers.cpp
    lib/debug.cpp
)

# *********************************************************************
# * Create 'ws-epaper-api' as a library
# * (Either static or shared depending on WSEPAPERAPI_STATIC option)
# *********************************************************************
if(WSEPAPERAPI_STATIC)
    message("WSEPAPERAPI_STATIC = \"${WSEPAPERAPI_STATIC}\", Building ws-epaper-api as a STATIC library")
    add_library(ws-epaper-api STATIC ${EPAPER_LIB_FILES})
else()
    message("WSEPAPERAPI_STATIC = \"${WSEPAPERAPI_STATIC}\", Building ws-epaper-api as a SHARED library")
    add_library(ws-epaper-api SHARED ${EPAPER_LIB_FILES})
endif()

# *********************************************************************
# * Add relevant headerfiles to include path
# *********************************************************************
target_include_directories(ws-epaper-api PUBLIC include)

if(ENABLE_EMULATION)
    target_include_directories(ws-epaper-api PUBLIC emulate)
endif()

# *********************************************************************
# * Add waveshare and bcm2835 code and link it with ws-epaper-api
# * (Though bcm2835 is not necessary on windows)
# *********************************************************************
add_subdirectory(external/waveshare)

if(WIN32)
    message(
        "Because you're building on Windows, bcm2835 cannot be included. As a result, there will be no crosscompilation support."
    )

    if(NOT ENABLE_EMULATION)
        message(WARNING
            "You did NOT enable emulation even though this is a windows build!"
            "\nYou should probably build with ENABLE_EMULATION = ON or there's really no point to building this library. "
            "Run cmake with -DENABLE_EMULATION=ON"
        )
    endif()

    # This copies over compiled DLL files into the same folder as ws-epaper-lib.dll
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
    )
else()
    add_subdirectory(external/bcm2835)

    target_include_directories(ws-epaper-api PUBLIC external/bcm2835/src)
    target_link_libraries(epaper PUBLIC bcm2835)
endif()

target_link_libraries(ws-epaper-api PUBLIC epaper)

# *********************************************************************
# * Enable C++17
# *********************************************************************
target_compile_features(
    ws-epaper-api PUBLIC cxx_std_17
)

# *********************************************************************
# * If emulation is enabled, look for the SDL library and link it
# *********************************************************************
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

    if(${WIN32})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
            COMMAND_EXPAND_LISTS
        )
    endif()

    if(TARGET SDL2::SDL2)
        target_link_libraries(ws-epaper-api PUBLIC SDL2::SDL2)
    else()
        target_link_libraries(ws-epaper-api PUBLIC SDL2)
    endif()
endif()

# *********************************************************************
# * Build examples if needed
# *********************************************************************
if(BUILD_EXAMPLES)
    message("BUILD_EXAMPLES = \"${BUILD_EXAMPLES}\", Adding ./examples directory to build...")

    if(NOT ENABLE_EMULATION)
        message(FATAL_ERROR
            "Building the examples requires emulation support! Set ENABLE_EMULATION to ON as well!"
        )
    endif()

    add_subdirectory(./examples)
endif()