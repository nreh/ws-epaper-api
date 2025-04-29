# ws-epaper-api

> [!IMPORTANT]  
> This is an experimental, work-in-progress library that I originally created for my own use. I've made it public, along with
> some documentation, in case it’s helpful to others. However, please note that most displays have not been tested with this
> code and as a result, it could be buggy or not run at all.
>
> Please consult
> [Waveshare's own example code](https://github.com/waveshareteam/e-Paper/tree/master/RaspberryPi_JetsonNano/c/examples) for
> your display before proceeding.

A lightweight C++ library for building GUIs on Waveshare e-paper displays with a Raspberry Pi. Includes an SDL-based display
emulator for cross-platform testing without requiring physical hardware. Supports 65 known displays.

![Demonstration](docs/screenshot_1.png)

Code for emulation window on the left:

```cpp
#include "emulate.h"
#include "EPD_2in13_V4.h"
#include "wsepaperapi.h"

#include "bitmaps/Moon.h"
#include "fonts/AllFonts.h"

using namespace std;
using namespace epaperapi;

int main() {
    //
    // Initialize emulator and renderer
    //

    typedef devices::EPD_2in13_V4::EPD_2in13_V4_DrawTarget device;
    EpaperEmulator target = EpaperEmulator::CreatePhysical<device>();
    Renderer renderer(target, BufferTransform::Rotate90Clockwise);

    //
    // Define fonts
    //

    typedef fonts::DinaBold_10pt font1;
    typedef fonts::Dina_6pt font2;

    //
    // Create and position elements
    //

    elements::TextElement<font1> text1("ws-epaper-api");
    text1.foregroundStyle.SetBlackChannel(0);
    text1.xpos = (250 / 2) - (text1.GetWidth() / 2);
    text1.ypos = 70;
    text1.characterSpacing = 0;
    renderer.elements.push_back(&text1);

    elements::TextElement<font2> text2("github.com/nreh/ws-epaper-api");
    text2.foregroundStyle.SetBlackChannel(0);
    text2.xpos = (250 / 2) - (text2.GetWidth() / 2);
    text2.ypos = text1.GetHeight() + text1.ypos;
    text2.characterSpacing = 0;
    renderer.elements.push_back(&text2);

    auto t = bitmaps::Moon();
    elements::Bitmap1BitElement img((250 / 2) - (t.GetWidth() / 2), 15, t);
    renderer.elements.push_back(&img);

    //
    // Render!
    //

    renderer.Refresh();
    KeepWindowOpen();
}
```

Code for physical display on the right:

```cpp
#include "EPD_2in13_V4.h"
#include "wsepaperapi.h"

#include "bitmaps/Moon.h"
#include "fonts/AllFonts.h"

using namespace std;
using namespace epaperapi;

int main() {
    //
    // Initialize device and renderer
    //

    devices::EPD_2in13_V4::EPD_2in13_V4_DrawTarget dev(false);
    Renderer renderer(dev, BufferTransform::Rotate90Clockwise);

    //
    // Initialize the display registers and clear to white
    //

    dev.Init();
    dev.Clear();

    //
    // Define fonts
    //

    typedef fonts::DinaBold_10pt font1;
    typedef fonts::Dina_6pt font2;

    //
    // Create and position elements
    //

    elements::TextElement<font1> text1("ws-epaper-api");
    text1.foregroundStyle.SetBlackChannel(0);
    text1.xpos = (250 / 2) - (text1.GetWidth() / 2);
    text1.ypos = 70;
    text1.characterSpacing = 0;
    renderer.elements.push_back(&text1);

    elements::TextElement<font2> text2("github.com/nreh/ws-epaper-api");
    text2.foregroundStyle.SetBlackChannel(0);
    text2.xpos = (250 / 2) - (text2.GetWidth() / 2);
    text2.ypos = text1.GetHeight() + text1.ypos;
    text2.characterSpacing = 0;
    renderer.elements.push_back(&text2);

    auto t = bitmaps::Moon();
    elements::Bitmap1BitElement img((250 / 2) - (t.GetWidth() / 2), 15, t);
    renderer.elements.push_back(&img);

    //
    // Render!
    //

    renderer.Refresh();

    //
    // Put device to sleep and exit
    //

    dev.Sleep();
    // According to waveshare's example code, we require a 2 second
    // delay between sleeping and exitting the device.
    devices::interface::bcm2835_delay(2000);
    dev.Exit();
}
```

See **[Examples Directory](examples)** for detailed examples on using the library.

## Features

- UI elements for creating complex interfaces
- Display emulation to test without physical e-paper display
- Pixel perfects fonts for displaying text
- Easily extensible for custom displays as well as your own UI elements

## Quick Links:

1. [I want to just build the library](#build-the-library)
2. [I want to use this library in my C++ project](#use-in-your-c-project)

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

Set `WSEPAPERAPI_STATIC` to TRUE to build as a **static** library.

```
mkdir build
cd build
cmake .. -DWSEPAPERAPI_STATIC=TRUE
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

## Use in your C++ Project

In your CMakeLists.txt simply add the directory containing this library and link it with your executable.

```cmake
add_subdirectory(ws-epaper-api)
target_link_libraries(your_executable PRIVATE ws-epaper-api)
```

For example, this is what a simple CMakeLists.txt could look like:

```cmake
cmake_minimum_required(VERSION 3.14)

project(
    "my_test_project"
    LANGUAGES C CXX
)

add_executable(my_test_program src/main.cpp)

add_subdirectory(extern/ws-epaper-api)
target_link_libraries(my_test_program PRIVATE ws-epaper-api)
```

Now you can import the required header file to draw to your display:

```cpp
#include "wsepaperapi.h"
```
