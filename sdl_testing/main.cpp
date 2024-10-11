#include <iostream>
#include <memory>
#include <vector>

#include "fonts/CourierPrime_14pt.h"
#include "sdlsetup.h"

using namespace std;

int main() {
    /**
     * Step 1: Setup SDL
     *
     * Pretty simple, this sets up the window and some variables for us
     */
    InitializeSDL(); // this also initializes sdlrenderer

    /**
     * Step 2: Setup the SDLDrawTarget to mimic the physical display we're using as close as possible.
     *
     * In this case, I have the 2.13 inch display and the EPD_MODEL is "EPD_2in13".
     *
     * Its dimensions are 250px by 122px
     *
     * And it is a grayscale display with either fully black or fully white (so grayscale steps = 2)
     */

    SDLDrawTarget sdlTarget(sdlrenderer, 250, 122, SDLDrawTarget::ColorMode::grayscale); // grayscale means no RGB color
    sdlTarget.GrayScaleSteps = 2; // the physical display can only render 2 grayscale steps, either fully black or white.
    epaperapi::Renderer epaperRenderer(sdlTarget);

    /**
     * Step 3: Setup elements that will be drawn and send them to the epaperRenderer
     *
     * Because we're using a grayscale display (SDLDrawTarget::COLORMODE::grayscale), we can't use the red, green, or blue
     * channel of ElementStyle.
     */

    // Create a diagonal line of boxes increasing in opacity.
    vector<shared_ptr<epaperapi::AbstractElement>> elements;
    for (int x = 0; x <= 13; x++) {
        auto elem = make_shared<epaperapi::elements::FilledRectangleElement>(50, 50);
        elements.push_back(elem);

        elem->xpos = x * 15;
        elem->ypos = x * 5;
        elem->style.SetBlackChannel(0);
        elem->style.alpha = x / 13.0f;

        epaperRenderer.elements.push_back(elem.get());
    }

    // draw white text above it all

    epaperapi::elements::TextElement<epaperapi::fonts::CourierPrime_14pt> text1("Hello World!");
    text1.foregroundStyle.SetBlackChannel(255);
    text1.xpos = (250 / 2) - (text1.GetWidth() / 2);
    text1.ypos = (122 / 2) - (text1.GetHeight() / 2);
    epaperRenderer.elements.push_back(&text1);

    /**
     * Step: 4: Refresh renderer
     */

    // This causes a redraw of all elements we just created
    // the results are sent to an internal buffer and then converted to an SDL texture
    // where it is then rendered on to the window.
    epaperRenderer.Refresh();

    /**
     * Step: 4.5: Make changes and refresh again!
     *
     * This increases the grayscale every half-second until we reach 255 steps
     */
    SDL_Event event;
    for (int i = sdlTarget.GrayScaleSteps; i <= 255; i++) {
        sdlTarget.GrayScaleSteps = i;
        cout << "Grayscale steps = " << i << endl;
        epaperRenderer.Refresh();

        SDL_Delay(250);

        while (SDL_PollEvent(&event)) {
            // allow the window to be closed
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }

        SDL_Delay(250);
    }

    /**
     * Step 5: End of code, keep window open
     *
     * If we have no other logic or things to test out, rather than exitting the program, this keeps the window open.
     */

    KeepWindowOpen(); // Don't exit the program immediately
}