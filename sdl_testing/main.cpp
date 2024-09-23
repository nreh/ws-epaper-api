#include <iostream>

#include "sdl.cpp"

using namespace std;

int main() {
    epaperapi::FilledRectangleElement rectangle1(250, 50);
    rectangle1.xpos = 0;
    rectangle1.ypos = 10;
    rectangle1.style = epaperapi::ElementStyle(0, 0, 0);

    epaperapi::FilledRectangleElement rectangle2(50, 50);
    rectangle2.xpos = 50;
    rectangle2.ypos = 20;
    rectangle2.style = epaperapi::ElementStyle(255, 0, 255, 0.0f);

    InitializeSDL();

    SDLDrawTarget sdlTarget(renderer, 250, 122);
    epaperapi::Renderer epaperRenderer(sdlTarget);

    epaperRenderer.elements.push_back(&rectangle1);
    epaperRenderer.elements.push_back(&rectangle2);
    epaperRenderer.Refresh();

    DisplaySDLWindow();
}