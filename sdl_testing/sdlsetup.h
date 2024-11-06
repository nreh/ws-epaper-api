#define SDL_MAIN_HANDLED

#if defined __has_include
    #if __has_include(<SDL2/SDL.h>)
        #include <SDL2/SDL.h>
    #else
        #include <SDL.h>
    #endif
#endif

#include <iostream>
#include <memory>
#include <string>

#include "wsepaperapi.h"

SDL_Renderer* sdlrenderer;
SDL_Window* window;

const int SDL_WINDOW_WIDTH = 700;
const int SDL_WINDOW_HEIGHT = 350;

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
    sdlrenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdlrenderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_SetRenderDrawColor(sdlrenderer, 200, 200, 200, 255);

    // Clear the screen with the white color
    SDL_RenderClear(sdlrenderer);
}

void KeepWindowOpen() {
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
    SDL_DestroyRenderer(sdlrenderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // causes a segmentation fault on WSL2 :/
}

/// @brief Rather than a physical display, this draw target draws to an SDL window. It can be useful for easily debugging
/// rendered images rather having to constantly print to a real display.
class SDLDrawTarget : public epaperapi::AbstractDrawTarget {
  public:
    /// @brief The target E-Ink may not be able to display in RGB as SDL is, so to test how the image will look on different
    /// capability displays, this setting can be used.
    enum class ColorMode {
        rgb,
        redblack,
        /// @brief Note: Also see `GrayScaleSteps` of SDLDrawTarget
        grayscale
    };

  private:
    SDL_Renderer* renderer;
    ColorMode colormode;

    /// @brief Converts Buffer to an SDL texture and renders it to the SDL window
    void DrawPixels() {
        texture = SDL_CreateTexture(sdlrenderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);

        uint8_t* data = new uint8_t[width * height * 3]; // 3 bytes (RGB) per pixel times total number of pixels

        switch (buffer.type()) {
        case epaperapi::BufferType::RGBBuffer: {
            const epaperapi::RGBBuffer* rgb = dynamic_cast<const epaperapi::RGBBuffer*>(&buffer);

            for (int i = 0; i < width * height; i++) {
                data[3 * i] = rgb->redChannel[i];
                data[3 * i + 1] = rgb->greenChannel[i];
                data[3 * i + 2] = rgb->blueChannel[i];
            }

            break;
        }

        case epaperapi::BufferType::RedBlackBuffer: {
            const epaperapi::RedBlackBuffer* rblk = dynamic_cast<const epaperapi::RedBlackBuffer*>(&buffer);

            for (int i = 0; i < width * height; i++) {
                data[3 * i] = rblk->redChannel[i];
                data[3 * i + 1] = rblk->blackChannel[i];
                data[3 * i + 2] = rblk->blackChannel[i];
            }

            break;
        }

        case epaperapi::BufferType::GrayscaleBuffer: {

            epaperapi::GrayscaleBuffer* blk = dynamic_cast<epaperapi::GrayscaleBuffer*>(&buffer);
            epaperapi::utils::PosterizeGrayscale(*blk, GrayScaleSteps);

            for (int i = 0; i < width * height; i++) {
                data[3 * i] = blk->blackChannel[i];
                data[3 * i + 1] = blk->blackChannel[i];
                data[3 * i + 2] = blk->blackChannel[i];
            }

            break;
        }
        }

        SDL_Rect rect;
        rect.x = SDL_WINDOW_WIDTH / 2 - (width / 2); // Centered on window
        rect.y = SDL_WINDOW_HEIGHT / 2 - (height / 2);
        rect.w = width;
        rect.h = height;

        // Draw the rectangle
        SDL_RenderFillRect(sdlrenderer, &rect);

        SDL_UpdateTexture(texture, NULL, data, width * 3);
        SDL_RenderCopy(sdlrenderer, texture, NULL, &rect);
    }

    /// @brief We really need only one render function, there's no concept or need of a "fast" or "partial" render for SDL.
    void RenderToSDL(epaperapi::AbstractBuffer& source) {
        // Clear screen
        SDL_SetRenderDrawColor(sdlrenderer, 200, 200, 200, 255);
        SDL_RenderClear(sdlrenderer);

        buffer.CopyBufferFrom(source);
        DrawPixels();

        SDL_RenderPresent(sdlrenderer);
    }

    /**
     * The created buffer and tempbuffer depends on the colormode which can/is defined at runtime by the user. This function
     * creates new instances of the buffer object depending on the value for colormode.
     *
     * This is a problem unique to SDLDrawTarget, so I'm not too worried about an elegant solution...
     */
    epaperapi::AbstractBuffer* CreateBufferBasedOnColorMode(uint16_t _width, uint16_t _height, ColorMode _colormode) {
        switch (_colormode) {
        case ColorMode::rgb:
            return new epaperapi::RGBBuffer(_width, _height);

        case ColorMode::redblack:
            return new epaperapi::RedBlackBuffer(_width, _height);

        case ColorMode::grayscale:
            return new epaperapi::GrayscaleBuffer(_width, _height);
        }

        return nullptr;
    }

  public:
    /// @brief If color mode is set to grayscale, this controls the steps between white and black. For example, for rendering
    /// where pixels can only be black (0) or white (255), it is 2.
    uint8_t GrayScaleSteps = 255;

    /**
     * @brief Construct a new SDLDrawTarget with an initialized SDL renderer and configuration
     *
     * @param _renderer An instance of `SDL_Renderer`
     * @param _width The width of the display in pixels
     * @param _height The height of the display in pixels
     * @param _mode To deal with the fact that different displays have different display capabilities, this mode can be
     * changed to change how color is rendered/stored to better emulate the physical display you're testing for. For example,
     * if `ColorMode::grayscale` is used, only the blackchannel is drawn. The default is rgb.
     */
    SDLDrawTarget(SDL_Renderer* _renderer, uint16_t _width, uint16_t _height, ColorMode _mode = ColorMode::rgb)
        : epaperapi::AbstractDrawTarget(*(this->CreateBufferBasedOnColorMode(_width, _height, _mode))) {
        renderer = _renderer;
        colormode = _mode;
    }

    /// @brief Refresh the display
    void Refresh(int mode) override { RenderToSDL(buffer); }

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

    ~SDLDrawTarget() { delete &buffer; }
};