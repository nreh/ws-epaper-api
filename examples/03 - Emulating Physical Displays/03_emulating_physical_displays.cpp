/**
 * 03 | Emulating Physical Displays
 *
 * This example demonstrates emulation of physical displays
 */

/**
 * Import the library headerfile, wsepaperapi.h
 */
#include "wsepaperapi.h"

/**
 * emulate.h contains the code for rendering to an SDL window so that we can visualize our rendered image on screen
 */
#include "emulate.h"

/**
 * Import the display that we will be drawing to. A complete list of displays and their capabilities can be found in
 * external/waveshare/ParsedCapabilities
 */
#include "EPD_2in13b_V4.h"

using namespace std;

int main() {

    /**
     * Step 1: Create EpaperEmulator with a physical display as reference
     *
     * In the previous example we defined the dimensions and color mode of the display manually when creating the
     * EpaperEmulator Draw-Target.
     *
     * Instead of that, we can use the CreatePhysical function to pass in a physical device to emulate. In this example we'll
     * use "2.13inch e-paper B V4" (https://www.waveshare.com/wiki/2.13inch_e-Paper_HAT_(B)_Manual).
     *
     * As an added benefit, the emulator will display the pixels exactly as they would appear on the physical display,
     * simulation the limited color palette and any grayscale steps.
     */

    // a bit verbose but you can use namespaces to clean it up in your own code...
    typedef epaperapi::devices::EPD_2in13b_V4::EPD_2in13b_V4_DrawTarget device;
    EpaperEmulator emulatorTarget = EpaperEmulator::CreatePhysical<device>(); // no need for dimensions or colormode!

    epaperapi::Renderer renderer(emulatorTarget);

    /**
     * Step 2: Create elements
     *
     * Like before, we create our overlappning rectangles. Since this display only supports red or black only those colors
     * are used.
     */

    // black rectangle
    epaperapi::elements::FilledRectangleElement rectangle(50, 50, 10, 10);
    renderer.AddElement(&rectangle);
    rectangle.style.SetRedBlackChannels(0, 0);

    // red rectangle
    epaperapi::elements::FilledRectangleElement rectangle2(50, 50, 25, 25);
    renderer.AddElement(&rectangle2);
    rectangle2.style.SetRedBlackChannels(255, 0);

    // black rectangle
    epaperapi::elements::FilledRectangleElement rectangle3(50, 50, 40, 40);
    renderer.AddElement(&rectangle3);
    rectangle3.style.SetRedBlackChannels(0, 0);

    /**
     * Step 3: Refresh the renderer.
     */
    renderer.Refresh();

    /**
     * Step 4: Keep the window open
     */
    KeepWindowOpen();
}