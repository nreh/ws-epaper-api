# ws-epaper-api

C++ library for displaying GUI on Waveshare's e-paper display using a Raspberry Pi.

## Quick Links:

1. [I want to just build the library](#build-the-library)
2. I want to use this library in another C++ project
3. I want to test my epaper display code

## Build the Library

### Shared Library

This will build the project as a **shared** library

```
mkdir build
cd build
cmake ..
cmake --build .
```

The build directory will look something like this:

```
.
├── CMakeCache.txt
├── CMakeFiles
│   └── . . .
├── Makefile
├── cmake_install.cmake
└── libepaperapi.so
```

With the `libepaperapi.so` file being the compiled library.

### Static Library

Set `EPAPERAPI_STATIC` to TRUE to build as a **static** library.

```
mkdir build
cd build
cmake .. -DEPAPERAPI_STATIC=TRUE
cmake --build .
```

The build directory will look something like this:

```
.
├── CMakeCache.txt
├── CMakeFiles
│   └── . . .
├── Makefile
├── cmake_install.cmake
└── libepaperapi.a
```

With the `libepaperapi.a` file being the compiled library.
