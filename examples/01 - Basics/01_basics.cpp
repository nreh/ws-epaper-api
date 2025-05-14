/**
 * 01 | Basics
 *
 * This example file demonstrates the basics of rendering to an SDL window.
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
     * Step 1: Create draw target
     *
     * Draw-Targets are things that have pixels draw onto. For example, it could be a physical epaper display of a certain
     * model number. But for this example, we're going to use EpaperEmulator which emulates an epaper display in a window.
     *
     * We'll emulate a simple RGB color display 500 pixels wide and 250 pixels tall.
     */
    EpaperEmulator emulatorTarget(500, 250, EpaperEmulator::ColorMode::rgb);

    /**
     * Step 2: Create a renderer
     *
     * The Renderer is what stores all the elements that will be drawn as well as how we trigger refreshes to the display.
     *
     * Usually it requires a physical epaper Draw-Target to draw on but we can pass the EpaperEmulator instead.
     */
    epaperapi::Renderer renderer(emulatorTarget);

    /**
     * Step 3: Elements
     *
     * Now we can actually create and manipulate elements that will be drawn to the screen. For this simple example, we'll
     * just draw a red rectangle in the middle of the screen.
     */
    epaperapi::elements::RectangleElement rectangle(50, 50, 500 / 2 - 25, 250 / 2 - 25); // (width,height,xpos,ypos)
    rectangle.fillStyle.SetRGBChannels(255, 0, 0); // style is how color is set for most elements

    /**
     * Step 4: Add elements to renderer
     */
    renderer.AddElement(&rectangle);

    /**
     * Step 5: Refresh the renderer. This wil automatically trigger a refresh of whatever display was passed in.
     *
     */
    renderer.Refresh();

    /**
     * Step 6: Keep the window open?
     *
     * If needed, you can keep the window open using the KeepWindowOpen() function in emulate.h
     */
    KeepWindowOpen();
}