/**
 * 02 | Color
 *
 * This example shows how elements can be given colors and transparency
 */

/**
 * Import the library headerfile, wsepaperapi.h
 */
#include "wsepaperapi.h"

/**
 * emulate.h contains the code for rendering to an SDL window so that we can visualize our rendered image on screen
 */
#include "emulate.h"

using namespace std;

int main() {

    /**
     * Step 1: Create draw target with RGB support and a renderer.
     */
    EpaperEmulator emulatorTarget(500, 250, EpaperEmulator::ColorMode::rgb);

    epaperapi::Renderer renderer(emulatorTarget);

    /**
     * Step 2: Create elements
     */
    epaperapi::elements::RectangleElement rectangle(100, 100, 10, 10);
    renderer.AddElement(&rectangle);

    // Most elements have some 'style' property that is used to set color. In this case, we'll make the rectangle green.
    rectangle.fillStyle.SetRGBChannels(0, 255, 0);

    // another red rectangle is placed above it but this time, it's slightly transparent
    epaperapi::elements::RectangleElement rectangle2(100, 100, 50, 50);
    renderer.AddElement(&rectangle2);

    rectangle2.fillStyle.SetRGBChannels(255, 0, 0);
    rectangle2.fillStyle.SetAlpha(0.75f); // the alpha channel is used to define transparency

    // finally, a black rectangle
    epaperapi::elements::RectangleElement rectangle3(100, 100, 85, 85);
    renderer.AddElement(&rectangle3);
    rectangle3.fillStyle.SetRGBChannels(0, 0, 0);

    /**
     * Step 3: Refresh the renderer.
     */
    renderer.Refresh();

    /**
     * Step 4: Keep the window open
     */
    KeepWindowOpen();
}