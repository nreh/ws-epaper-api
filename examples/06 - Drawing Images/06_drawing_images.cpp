/**
 * 06 | Drawing Images
 *
 * This example shows how to draw 1-bit bitmap images using the Bitmap1BitElement
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

/**
 * Import desired bitmap. In this case, we're drawing the Wifi logo.
 */
#include "bitmaps/Wifi.h"

using namespace std;
using namespace epaperapi;

int main() {

    /**
     * Step 1: Create EpaperEmulator with a physical display as reference
     */

    typedef devices::EPD_2in13b_V4::EPD_2in13b_V4_DrawTarget device;
    EpaperEmulator emulatorTarget = EpaperEmulator::CreatePhysical<device>();

    Renderer renderer(emulatorTarget);

    /**
     * Step 2: Instantiate wifi logo and use  Bitmap1BitElement to draw on screen
     */

    bitmaps::Wifi wifiLogo;

    elements::Bitmap1BitElement bitmapRenderer(10, 10, wifiLogo);
    renderer.AddElement(&bitmapRenderer);

    elements::Bitmap1BitElement redBitmapRenderer(10, 60, wifiLogo);
    redBitmapRenderer.foregroundStyle.SetRedBlackChannels(255, 0); // we can also make it red!
    renderer.AddElement(&redBitmapRenderer);

    // See the scripts/bitmapconversion folder for instructions on creating your own bitmaps from .bmp files.

    /**
     * Step 3: Refresh the renderer.
     */
    renderer.Refresh();

    /**
     * Step 4: Keep the window open
     */
    KeepWindowOpen();
}