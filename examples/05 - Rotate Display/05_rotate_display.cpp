/**
 * 05 | Rotate Display
 *
 * This example shows how to rotate/transform before rendering to a display.
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
 * Import all fonts
 */
#include "fonts/AllFonts.h"

using namespace std;
using namespace epaperapi;

int main() {

    /**
     * Step 1: Create EpaperEmulator with a physical display as reference
     */

    typedef devices::EPD_2in13b_V4::EPD_2in13b_V4_DrawTarget device;
    EpaperEmulator emulatorTarget = EpaperEmulator::CreatePhysical<device>();

    Renderer renderer(emulatorTarget);

    // In the previous example, we were limited by the narrow width of the '2in13b_V4' display. To get around this, we can
    // rotate our image before drawing to the display using a transformation.
    renderer.SetTransformation(BufferTransform::Rotate90Clockwise);

    /**
     * Step 2: Create lines of text using TextElement
     */

    elements::TextElement<fonts::DinaBold_10pt> helloWorld("Hello World!");
    renderer.AddElement(&helloWorld);

    elements::TextElement<fonts::Dina_8pt> text2("Now we can write longer lines of text!");
    text2.characterSpacing = -1; // decrease character spacing slightly so that the text fits on screen
    text2.xpos = 3;
    text2.ypos = 30;
    renderer.AddElement(&text2);

    /**
     * Step 3: Refresh the renderer.
     */
    renderer.Refresh();

    /**
     * Step 4: Keep the window open
     */
    KeepWindowOpen();
}