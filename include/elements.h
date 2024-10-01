#pragma once

#include <stdint.h>

namespace epaperapi {

class AbstractBuffer;

/// @brief Contains color information used by buffers for drawing. Certain values are unused depending on the type of buffer.
/// For example, the Grayscale buffer would not use any of the red green or blue color channels.
struct ElementStyle {
    /// @brief Used by RGBBuffer and RedBlackBuffer
    uint8_t redChannel = 0;

    /// @brief Used by RGBBuffer
    uint8_t greenChannel = 0;

    /// @brief Used by RGBBuffer
    uint8_t blueChannel = 0;

    /// @brief Used by GrayscaleBuffer and RGBBuffer
    uint8_t blackChannel = 0;

    /// @brief Transparency of the element
    float alpha = 1;

    ElementStyle(uint8_t r, uint8_t g, uint8_t b) : redChannel(r), greenChannel(g), blueChannel(b) {}
    ElementStyle(uint8_t r, uint8_t black) : redChannel(r), blackChannel(black) {}
    ElementStyle(uint8_t black) : blackChannel(black) {}
    ElementStyle() {}

    ElementStyle& SetRedChannel(uint8_t red) {
        redChannel = red;
        return *this;
    }
    ElementStyle& SetGreenChannel(uint8_t green) {
        greenChannel = green;
        return *this;
    }
    ElementStyle& SetBlueChannel(uint8_t blue) {
        blueChannel = blue;
        return *this;
    }
    ElementStyle& SetRGBChannels(uint8_t r, uint8_t g, uint8_t b) {
        redChannel = r;
        greenChannel = g;
        blueChannel = b;
        return *this;
    }
    ElementStyle& SetBlackChannel(uint8_t black) {
        blackChannel = black;
        return *this;
    }
    ElementStyle& SetRedBlackChannels(uint8_t r, uint8_t b) {
        redChannel = r;
        blackChannel = b;
        return *this;
    }
    ElementStyle& SetAlpha(float _alpha) {
        alpha = _alpha;
        return *this;
    }
};

/// @brief Abstract class representing something that can be drawn to
class AbstractElement {
  public:
    /// @brief If false, this Element is not drawn
    bool visible = true;

    uint16_t xpos, ypos;
    ElementStyle style;

    /// @brief Draw this element to a buffer
    /// @param _buffer
    virtual void Draw(AbstractBuffer& target) = 0;
};

class FilledRectangleElement : public AbstractElement {
  public:
    uint16_t width, height;
    uint16_t xpos = 0, ypos = 0;

    FilledRectangleElement(uint16_t _width, uint16_t _height);

    /// @brief Draw the FilledRectangle to the target buffer
    /// @param target
    void Draw(AbstractBuffer& target) override;
};
} // namespace epaperapi