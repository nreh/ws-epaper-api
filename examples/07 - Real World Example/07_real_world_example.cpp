/**
 * 07 | Real World Example
 *
 * This example shows how to draw to an actual display
 */

/**
 * Import the library headerfile, wsepaperapi.h. Note that the emulate.h header is not included this time.
 */
#include "wsepaperapi.h"

/**
 * Import the display that we will be drawing to. A complete list of displays and their capabilities can be found in
 * external/waveshare/ParsedCapabilities
 */
#include "EPD_2in13b_V4.h"

using namespace std;
using namespace epaperapi;

int main() {

    /**
     * Step 1: Create a draw target for the display and assign it to a new renderer.
     *
     * In the previous example, we used the EpaperEmulator to be able to simulate the e-paper display. This time,
     * because we're rendering to a real display we can create the draw target and render directly to it.
     */

    auto device = devices::EPD_2in13b_V4::EPD_2in13b_V4_DrawTarget();
    Renderer renderer(device);

    /**
     * Step 2: Create a simple box
     */

    elements::RectangleElement box(25, 25, 25, 25);
    box.fillStyle.SetBlackChannel(0); // black rectangle
    renderer.AddElement(&box);

    /**
     * Step 3: Refresh the renderer.
     */
    renderer.Refresh();

    /**
     * Step 4: We want to put the display to sleep and close the SPI connection after drawing.
     *
     * According to the example code given by Waveshare that can be found here:
     * https://github.com/waveshareteam/e-Paper/blob/master/RaspberryPi_JetsonNano/c/examples/EPD_2in13_V4_test.c
     * we must put the display to sleep and then - after a delay of at least 2 seconds - close the SPI connection so that the
     * display enters 0 power consumption mode.
     */
    device.Sleep();

    /**
     * Wait for at least 2 seconds - Waveshare's example indicates that this is important!
     *
     * To do this, you can use the namespace devices::interface to access the underlying bcm library which lets you execute
     * code for the Broadcom BCM 2835 which is used in the Raspberry Pi.
     */
    devices::interface::bcm2835_delay(2000);

    device.Exit(); // Shuts off power to the device, ends SPI protocol, and deallocates memory
}