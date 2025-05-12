/**
 * 08 | Demonstration of Elements
 *
 * This example showcases different elements included with the library
 */

/**
 * Import the library headerfiles including emulation support
 */
#include "emulate.h"
#include "wsepaperapi.h"

#include "bitmaps/Bluetooth.h"
#include "fonts/AllFonts.h"

using namespace std;
using namespace epaperapi;

int main() {

    /**
     * Step 1: Create draw target
     */

    auto emulator = EpaperEmulator(650, 300, EpaperEmulator::ColorMode::rgb);
    Renderer renderer(emulator);

    /**
     * Step 3: Create UI elements
     */

    typedef fonts::Dina_6pt font;

    elements::FilledRectangleElement box1(25, 25, 70, 25);
    renderer.AddElement(&box1);

    elements::TextElement<font> description1("FilledRectangleElement");
    description1.xpos = box1.xpos + 12 - (description1.GetWidth() / 2);
    description1.ypos = 70;
    renderer.AddElement(&description1);

    elements::LineElement line(175, 20, 230, 25);
    renderer.AddElement(&line);

    elements::TextElement<font> description2("LineElement");
    description2.xpos = 170;
    description2.ypos = 70;
    renderer.AddElement(&description2);

    elements::ProgressBarElement progress;
    progress.xpos = 285;
    progress.ypos = 40;
    progress.width = 70;
    progress.progress = 0.75f;
    progress.variant = elements::ProgressBarElement::Variants::Skeuomorphic;
    progress.backgroundStyle.SetRGBChannels(255, 255, 255); // white highlight for skeumorphic
    renderer.AddElement(&progress);

    elements::TextElement<font> description3("ProgressBarElement");
    description3.xpos = 265;
    description3.ypos = 70;
    renderer.AddElement(&description3);

    bitmaps::Bluetooth bt;
    elements::Bitmap1BitElement image(440, 35, bt);
    renderer.AddElement(&image);

    elements::TextElement<font> description4("Bitmap1BitElement");
    description4.xpos = 400;
    description4.ypos = 70;
    renderer.AddElement(&description4);

    elements::TextElement<fonts::Unifont_16pt> text("Hello World!");
    text.xpos = 520;
    text.ypos = 35;
    renderer.AddElement(&text);

    elements::TextElement<font> description5("TextElement");
    description5.xpos = 530;
    description5.ypos = 70;
    renderer.AddElement(&description5);

    /**
     * Step 4: Refresh the renderer and keep window open
     */
    renderer.Refresh();
    KeepWindowOpen();
}