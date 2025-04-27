/**
 * 04 | Text
 *
 * This example shows how to render text using the TextElement and fonts.
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

    /**
     * Step 2: Create lines of text using TextElement
     */

    // The TextElement is used to render text. It takes a font that derives from AbstractFont as a template.
    // See the scripts/fontmaking folder for more information on creating and using your own fonts

    elements::TextElement<fonts::DinaBold_10pt> helloWorld("Hello World!");
    renderer.AddElement(&helloWorld);

    elements::TextElement<fonts::Roboto_12pt> text2("Some fonts are buggy");
    text2.ypos = 30;
    renderer.AddElement(&text2);

    elements::TextElement<fonts::Unifont_14pt> text3("Others are good");
    text3.ypos = 60;
    renderer.AddElement(&text3);

    /**
     * Step 3: Refresh the renderer.
     */
    renderer.Refresh();

    /**
     * Step 4: Keep the window open
     */
    KeepWindowOpen();
}