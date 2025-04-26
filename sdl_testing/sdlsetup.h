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
#include <type_traits>

#include "wsepaperapi.h"

SDL_Renderer* sdlrenderer;
SDL_Window* window;

const int SDL_WINDOW_WIDTH = 1000;
const int SDL_WINDOW_HEIGHT = 980;

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
/// rendered images rather having to constantly print to a real display. This draw target can be created manually using the
/// constructor by passing in width, height, and mode information. However, you can also use the `CreateFromDevice<Device>()`
/// function to create a draw target that will simulate the physical display.
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

    enum class DrawMode {
        /// @brief Pixels are drawn as normal to the screen.
        normal,
        /// @brief Pixels are first drawn to a virtual EPD device and then unpacked and drawn to screen. Useful for testing
        /// how rendering will look on a real EPD display with limited colors or grayscale steps.
        physical
    };

  private:
    SDL_Renderer* renderer;
    ColorMode colormode;
    /// @brief If specified, the rendered pixels are first preprocessed on this device before being rendered on screen
    /// effectively letting us render exactly how renderingw will look on the physical display.
    epaperapi::devices::PhysicalEPDDrawTarget* physicalReferenceDevice = nullptr;

    /// @brief Converts Buffer to an SDL texture and renders it to the SDL window
    void DrawPixels() {
        texture = SDL_CreateTexture(sdlrenderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height);

        uint8_t* data = new uint8_t[width * height * 3]; // 3 bytes (RGB) per pixel times total number of pixels

        if (physicalReferenceDevice != nullptr && NoPhysicalDrawMode == false) {
            // if we have a physical reference device, we perform an extra step where we preprocess the buffer before
            // unpacking again and rendering to screen.
            physicalReferenceDevice->PreprocessBuffers();
            physicalReferenceDevice->UnpackBuffers(buffer);
        }

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
                auto r = rblk->redChannel[i];
                auto gb = rblk->blackChannel[i];

                if (r == 255) { // prioritize red color
                    gb = 0;
                } else if (gb > 0) {
                    r = gb; // seting black channel to 255 should render white (assuming red channel is set to 0)
                }

                data[3 * i] = r;      // R
                data[3 * i + 1] = gb; // G
                data[3 * i + 2] = gb; // B
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

    /// @brief Used by CreateFromDevice()
    SDLDrawTarget(SDL_Renderer* _renderer, epaperapi::devices::PhysicalEPDDrawTarget* _device, ColorMode _mode)
        : epaperapi::AbstractDrawTarget(_device->GetBuffer()), // use the physical device's buffer rather than creating new
          physicalReferenceDevice(_device) {
        renderer = _renderer;
        colormode = _mode;
    }

  public:
    /// @brief If color mode is set to grayscale, this controls the steps between white and black. For example, for rendering
    /// where pixels can only be black (0) or white (255), it is 2.
    uint8_t GrayScaleSteps = 255;

    /// @brief When set to true, the Normal drawmode is used instead of Physical even if a physical device is set. (See
    /// GetDrawMode() and CreatePhysical() for more information)
    bool NoPhysicalDrawMode = false;

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

    /// @brief Rather than manually creating the SDLDrawTarget by setting width, height, mode, etc... this function
    /// automatically pulls this information from the given EPD device passed as a template parameter. In addition, the draw
    /// mode will be set to 'physical' meaning that all draw calls are preprocessed using this device to get a more accurate
    /// simulation of what the rendered image will look on the display. For example, it's useful for seeing how colors will
    /// be quantized on the physical display - something that isn't possible when creating SDLDrawTarget manually. By setting
    /// `NoPhysicalDrawMode` to true you can disable this behavior and force Normal drawing logic.
    /// @tparam Device A class representing an EPD device, must derive from `PhysicalEPDDrawTarget`
    /// @return New instance of SDLDrawTarget that draws in 'physical' mode rather than 'normal' (Unless `NoPhysicalDrawMode`
    /// is set to true.)
    template <typename Device> static SDLDrawTarget CreatePhysical(SDL_Renderer* _renderer) {
        typedef epaperapi::devices::PhysicalEPDDrawTarget PhysicalEPD;

        static_assert(
            std::is_base_of<PhysicalEPD, Device>::value, "Device must derive from epaperapi::devices::PhysicalEPDDrawTarget!"
        );

        PhysicalEPD* inst = new Device(false); // create new instance without initializing SPI

        ColorMode mode;

        switch (inst->GetBuffer().type()) {
        case epaperapi::BufferType::GrayscaleBuffer:
            mode = ColorMode::grayscale;
            break;

        case epaperapi::BufferType::RedBlackBuffer:
            mode = ColorMode::redblack;
            break;

        case epaperapi::BufferType::RGBBuffer:
            mode = ColorMode::rgb;
            break;

        default:
            throw std::runtime_error("Given device is unsupported by SDLDrawTarget.");
            break;
        }

        return SDLDrawTarget(_renderer, inst, mode);
    }

    DrawMode GetDrawMode() const {
        if (physicalReferenceDevice == nullptr) {
            return DrawMode::normal;
        } else {
            return DrawMode::physical;
        }
    }

    ~SDLDrawTarget() {
        if (physicalReferenceDevice != nullptr) {
            delete physicalReferenceDevice;
        } else {
            delete &buffer; // this means SDLDrawTarget owns the buffer and is responsible for deleting it
        }
    }
};