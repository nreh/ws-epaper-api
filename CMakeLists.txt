# This CMakeLists file supports two types of build modes. Either for testing or for building the library

if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR
        "IN-SOURCE BUILD NOT ALLOWED!\n"
        "You're not allowed to build in this folder."
        " Please create a separate build subdirectory and run 'cmake ..' from there.\n"
        "If you're unsure what this means, follow the steps for building in the README exactly.\n"
        "Also, you should delete the newly created 'CMakeCache.txt' file and 'CMakeFiles/' directory that were just created."
    )
endif()

if(NOT DEFINED EPAPERLIB_MODE)
    message(
        FATAL_ERROR
        "EPAPERLIB_MODE is not defined. Please set to one of the following:\n • LIBRARY\n • SDL_TESTING\n"
        "See README for explanations on what these options mean."
    )
endif()

if(EPAPERLIB_MODE STREQUAL "LIBRARY")
    message("EPAPERLIB_MODE = \"${EPAPERLIB_MODE}\", Building epaperlib as a STATIC library")

elseif(EPAPERLIB_MODE STREQUAL "SDL_TESTING")
    message("EPAPERLIB_MODE = \"${EPAPERLIB_MODE}\", Building epaperlib in testing mode with the SDL library.")
endif()