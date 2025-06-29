/**
 * 10 | Demonstration of the Canvas Element
 *
 * This example shows how the Canvas Element can be used to rotate other elements
 */

/**
 * Import the library headerfiles including emulation support
 */
#include "emulate.h"
#include "wsepaperapi.h"

#include "fonts/AllFonts.h"

#include "bitmaps/Lightning.h"

using namespace std;
using namespace epaperapi;

int main() {

    /**
     * Step 1: Create draw target
     */

    auto emulator = EpaperEmulator(400, 300, EpaperEmulator::ColorMode::rgb);
    Renderer renderer(emulator);

    /**
     * Step 2: Create two canvases, one rotated 90 degrees and populate them
     */

    int canvasWidth = 80;
    int canvasHeight = 50;

    // the canvas element requires the containing buffer that it will be drawn on to
    elements::CanvasElement canvas1(emulator.buffer, 115, 120, canvasWidth, canvasHeight);
    elements::CanvasElement canvas2(
        emulator.buffer, 235, 100, canvasWidth, canvasHeight, BufferTransform::Rotate90CounterClockwise
    );

    bitmaps::Lightning lightningBmp;
    elements::Bitmap1BitElement lightningImg(15, 0, &lightningBmp);

    elements::TextElement<fonts::Dina_10pt> text1("Canvas 1");
    text1.ypos = 25;
    elements::TextElement<fonts::Dina_10pt> text2("Canvas 2");
    text2.ypos = 25;

    canvas1.AddElement(&text1);
    canvas2.AddElement(&text2);

    // we can reuse the image between the two canvases
    canvas1.AddElement(&lightningImg);
    canvas2.AddElement(&lightningImg);

    renderer.AddElement(&canvas1);
    renderer.AddElement(&canvas2);

    /**
     * Step 3: Important! Refresh the canvas so that the elements added to it are rendered
     */

    canvas1.Refresh();
    canvas2.Refresh();

    /**
     * Step 4: Refresh the renderer and keep window open
     */
    renderer.Refresh();
    KeepWindowOpen();
}