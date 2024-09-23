#include <iostream>

#include "sdl.cpp"

using namespace std;

int main() {
    epaperapi::FilledRectangleElement rectangle1(50, 50);
    rectangle1.xpos = 50;
    rectangle1.ypos = 50;
    rectangle1.style = epaperapi::ElementStyle(255, 0, 0, 0.7f);

    epaperapi::FilledRectangleElement rectangle2(50, 50);
    rectangle2.xpos = 60;
    rectangle2.ypos = 60;
    rectangle2.style = epaperapi::ElementStyle(0, 255, 0, 0.7f);

    epaperapi::FilledRectangleElement rectangle3(50, 50);
    rectangle3.xpos = 70;
    rectangle3.ypos = 70;
    rectangle3.style = epaperapi::ElementStyle(0, 0, 255, 0.7f);

    InitializeSDL();

    SDLDrawTarget sdlTarget(renderer, 250, 250);
    epaperapi::Renderer epaperRenderer(sdlTarget);

    epaperRenderer.elements.push_back(&rectangle1);
    epaperRenderer.elements.push_back(&rectangle2);
    epaperRenderer.elements.push_back(&rectangle3);
    epaperRenderer.Refresh();

    DisplaySDLWindow();
}