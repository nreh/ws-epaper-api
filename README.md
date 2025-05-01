# ws-epaper-api

> [!IMPORTANT]  
> This is an experimental, work-in-progress library that I originally created for my own use. I've made it public, along with
> some documentation, in case it’s helpful to others. However, please note that most displays have not been tested with this
> code and as a result, many display types could be buggy or not run at all.
>
> Please consult
> [Waveshare's own example code](https://github.com/waveshareteam/e-Paper/tree/master/RaspberryPi_JetsonNano/c/examples) for
> your display before proceeding.

A lightweight C++ library for building GUIs on Waveshare e-paper displays with a Raspberry Pi. Includes an SDL-based display
emulator for cross-platform testing without requiring physical hardware. Supports 65 known displays.

![Demonstration](docs/screenshot_1.png)

<details>

<summary>🔍 Click to see the code for the above image</summary>

## Code for emulation window on the left:

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

## Code for physical display on the right:

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

</details>

&nbsp;

> [!NOTE]  
> See **[Examples Directory](examples)** for detailed examples on using the library.

&nbsp;

## ⭐ Features

- UI elements for creating complex interfaces
- Display emulation to test without a physical e-paper display
- Pixel perfects fonts for displaying text and scripts for creating your own
- Easily extensible for custom displays as well as your own UI elements

## 🔗 Quick Links:

1. [I want to use this library in my C++ project](#-use-in-your-c-project)
2. [I want to build the examples](#-build-the-examples)
3. [I want to build as a library](#-build-the-library)

&nbsp;

&nbsp;

## ⚡ Use in your C++ Project

In your CMakeLists.txt simply add the directory containing all the source code here and link it with your executable.

```
git clone https://github.com/nreh/ws-epaper-api
```

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

Then import the required header file:

```cpp
#include "wsepaperapi.h"
```

And finally the headerfile corresponding to your display. A complete list of header files that you can import can be found in
[`external/waveshare/DrawTargets`](external/waveshare/DrawTargets).
[For example, if you have this display](https://www.waveshare.com/2.13inch-e-paper-hat.htm), you'd import:

```cpp
#include "EPD_2in13_V4.h"
```

> [!IMPORTANT]  
> To use the emulation feature, the `ENABLE_EMULATION` option must be set to TRUE or ON. In addition, you must have the SDL
> library installed on your machine where CMake can find it.
>
> Once enabled, you can get the required functions/classes for emulation by important `emulate.h`:
>
> ```cpp
> #include "wsepaperapi.h"
> #include "emulate.h"
> ```
>
> See the examples for more information.

&nbsp;

## 🔨 Build the Examples

```
mkdir build
cd build
cmake -DBUILD_EXAMPLES=TRUE -DENABLE_EMULATION=TRUE ..
cmake --build .
```

The resulting executable binaries will be located in the `build/examples/` directory.

&nbsp;

## 🔨 Build the Library

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
└── libws-epaper-api.so
```

With the `libws-epaper-api.so` file being the compiled library.

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
└── libws-epaper-api.a
```

With the `libws-epaper-api.a` file being the compiled library.
