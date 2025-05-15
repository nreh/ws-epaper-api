/**
 * 09 | Demonstration of Custom Elements
 *
 * This example shows how custom elements can be created by extending the AbstractElement class
 */

/**
 * Import the library headerfiles including emulation support
 */
#include "emulate.h"
#include "wsepaperapi.h"

#include "fonts/AllFonts.h"

using namespace std;
using namespace epaperapi;

/**
 * Step 1: Create simple ToggleSwitch element
 */

class ToggleSwitch : public AbstractElement {
  protected:
    elements::TextElement<fonts::Dina_8pt> label;

  public:
    bool isToggledOn = false;

    void Draw(AbstractBuffer& drawTarget) override {
        drawTarget.DrawRectangle(xpos, ypos, 40, 20, ElementStyle(0, 0, 0));
        label.xpos = xpos + 50;
        label.ypos = ypos + 5;

        if (isToggledOn == false) {
            drawTarget.DrawFilledRectangle(xpos + 2, ypos + 2, 16, 16, ElementStyle(128, 128, 128));
            label.text = "Disabled";
        } else {
            drawTarget.DrawFilledRectangle(xpos + 40 - 16 - 2, ypos + 2, 16, 16, ElementStyle(0, 0, 0));
            label.text = "Enabled";
        }

        label.Draw(drawTarget);
    }
};

int main() {

    /**
     * Step 2: Create draw target
     */

    auto emulator = EpaperEmulator(400, 300, EpaperEmulator::ColorMode::rgb);
    Renderer renderer(emulator);

    /**
     * Step 3: Use custom element
     */

    ToggleSwitch toggleSwitch1;
    toggleSwitch1.xpos = 25;
    toggleSwitch1.ypos = 25;
    toggleSwitch1.isToggledOn = false;
    renderer.AddElement(&toggleSwitch1);

    ToggleSwitch toggleSwitch2;
    toggleSwitch2.xpos = 25;
    toggleSwitch2.ypos = 60;
    toggleSwitch2.isToggledOn = true;
    renderer.AddElement(&toggleSwitch2);

    /**
     * Step 4: Refresh the renderer and keep window open
     */
    renderer.Refresh();
    KeepWindowOpen();
}