#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>

#include <epaperapi.h>

SDL_Renderer* renderer;
SDL_Window* window;

const int SDL_WINDOW_WIDTH = 800;
const int SDL_WINDOW_HEIGHT = 600;

SDL_Texture* texture;

void InitializeSDL() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    // Create a window
    window = SDL_CreateWindow(
        "SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, SDL_WINDOW_SHOWN
    );
    if (!window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    // Clear the screen with the white color
    SDL_RenderClear(renderer);
}

void DrawSinglePixel(uint16_t xpos, uint16_t ypos, epaperapi::ElementStyle value) {}

/// @brief Converts Buffer to an SDL texture and renders it to the SDL window
void DrawPixels(epaperapi::AbstractBuffer& buffer, uint16_t width, uint16_t height) {
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);

    uint8_t* data = new uint8_t[width * height * 3]; // 3 bytes (RGB) per pixel times total number of pixels

    switch (buffer.type()) {
    case epaperapi::BUFFERTYPE::RGBBuffer: {
        const epaperapi::RGBBuffer* rgb = dynamic_cast<const epaperapi::RGBBuffer*>(&buffer);

        for (int i = 0; i < width * height; i++) {
            data[3 * i] = rgb->redChannel[i];
            data[3 * i + 1] = rgb->greenChannel[i];
            data[3 * i + 2] = rgb->blueChannel[i];
        }

        break;
    }

    case epaperapi::BUFFERTYPE::RedBlackBuffer: {
        const epaperapi::RedBlackBuffer* rblk = dynamic_cast<const epaperapi::RedBlackBuffer*>(&buffer);

        break;
    }

    case epaperapi::BUFFERTYPE::GrayscaleBuffer: {
        const epaperapi::GrayscaleBuffer* rblk = dynamic_cast<const epaperapi::GrayscaleBuffer*>(&buffer);

        break;
    }
    }

    // Set the draw color to red (RGBA: 255, 0, 0, 255)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect rect;
    rect.x = SDL_WINDOW_WIDTH / 2 - (width / 2); // Centered on window
    rect.y = SDL_WINDOW_HEIGHT / 2 - (height / 2);
    rect.w = width;
    rect.h = height;

    // Draw the rectangle
    SDL_RenderFillRect(renderer, &rect);

    SDL_UpdateTexture(texture, NULL, data, width * 3);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void DisplaySDLWindow() {
    SDL_RenderPresent(renderer);

    // Event loop to keep the window open
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
}

/// @brief Drawing target used for drawing to an SDL window
class SDLDrawTarget : public epaperapi::AbstractDrawTarget {
  public:
    /// @brief The target E-Ink may not be able to display in RGB as SDL is, so to test how the image will look on different
    /// capability displays, this setting can be used.
    enum class COLORMODE { rgb, redblack, grayscale };

  private:
    SDL_Renderer* renderer;
    uint16_t width, height;
    COLORMODE colormode;

    /// @brief We really need only one render function, there's no concept or need of a "fast" or "partial" render for SDL.
    void RenderToSDL(epaperapi::AbstractBuffer& source) {
        buffer.CopyBufferFrom(source);
        DrawPixels(buffer, width, height);
    }

    /**
     * The created buffer and tempbuffer depends on the colormode which can/is defined at runtime by the user. This function
     * creates new instances of the buffer object depending on the value for colormode.
     *
     * This is a problem unique to SDLDrawTarget, so I'm not too worried about an elegant solution...
     */
    epaperapi::AbstractBuffer* CreateBufferBasedOnColorMode(uint16_t _width, uint16_t _height, COLORMODE _colormode) {
        switch (_colormode) {
        case COLORMODE::rgb:
            return new epaperapi::RGBBuffer(_width, _height);

        case COLORMODE::redblack:
            return new epaperapi::RedBlackBuffer(_width, _height);

        case COLORMODE::grayscale:
            return new epaperapi::GrayscaleBuffer(_width, _height);
        }

        return nullptr;
    }

  public:
    /// @brief If color mode is set to grayscale, this controls the steps between white and black. For example, for rendering
    /// where pixels can only be black (0) or white (255), it is 2.
    uint8_t GrayScaleSteps = 255;

    SDLDrawTarget(SDL_Renderer* _renderer, uint16_t _width, uint16_t _height, COLORMODE _mode = COLORMODE::rgb)
        : width(_width), height(_height),
          epaperapi::AbstractDrawTarget(
              *(this->CreateBufferBasedOnColorMode(_width, _height, _mode)),
              *(this->CreateBufferBasedOnColorMode(_width, _height, _mode)) // can't believe this works lol
          ) {
        renderer = _renderer;
        colormode = _mode;
    }

    /// @brief Refresh the display
    void Refresh(epaperapi::AbstractBuffer& _buffer) override { RenderToSDL(_buffer); }

    /// @brief Do a fast refresh
    void RefreshFast(epaperapi::AbstractBuffer& _buffer) override { RenderToSDL(_buffer); }

    /// @brief Partially refresh the display
    void PartialRefresh(epaperapi::AbstractBuffer& _buffer) override { RenderToSDL(_buffer); }

    /// @brief Clear the display to white
    void Clear() { // Set render color to white (RGBA: 255, 255, 255, 255)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Clear the screen with the white color
        SDL_RenderClear(renderer);
    }

    /// @brief Clear the display to black
    void ClearBlack() { // Set render color to black (RGBA: 255, 0, 0, 0)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Clear the screen with the black color
        SDL_RenderClear(renderer);
    }

    void Init() override {}
    void Sleep() override {}
};