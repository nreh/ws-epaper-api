#include <iostream>
#include <vector>

#include "sdlsetup.h"

using namespace std;

int main() {
    vector<epaperapi::FilledRectangleElement> rectangles;

    for (int x = 0; x <= 35; x++) {
        rectangles.push_back(epaperapi::FilledRectangleElement(50, 50));
        rectangles[x].xpos = x * 5;
        rectangles[x].ypos = x * 5;
        rectangles[x].style = epaperapi::ElementStyle(0);
        rectangles[x].style.alpha = x / 35.0f;
    }

    InitializeSDL(); // this also initializes sdlrenderer

    SDLDrawTarget sdlTarget(sdlrenderer, 250, 250, SDLDrawTarget::COLORMODE::grayscale);
    sdlTarget.GrayScaleSteps = 3;
    epaperapi::Renderer epaperRenderer(sdlTarget);

    for (auto& r : rectangles) {
        epaperRenderer.elements.push_back(&r);
    }

    epaperRenderer.Refresh();

    DisplaySDLWindow(); // this will poll until the window is closed

    SDL_Quit(); // causes a segmentation fault on WSL2 :/
}