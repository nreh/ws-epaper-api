#include "buffers.h"
#include "bufferutils.h"
#include "elements.h"
#include "utils.h"

#include <cstring>
#include <string>
#include <type_traits>

namespace epaperapi {

/// @brief Get pixel in a packed array of bytes
inline bool getPixel(const uint8_t* bitmap, size_t width, size_t i, size_t j) {
    // Calculate the 1D index from 2D coordinates
    size_t n = j * width + i;

    // Calculate byte index and bit position
    size_t byte_index = n / 8;
    size_t bit_position = n % 8;

    // Extract the pixel value (0 or 1)
    return (bitmap[byte_index] >> (7 - bit_position)) & 0x01;
}

AbstractBuffer::AbstractBuffer(uint16_t _width, uint16_t _height) : width(_width), height(_height) {
    alphaChannel = new float[width * height];
}

AbstractBuffer::~AbstractBuffer() { delete[] alphaChannel; }

RGBBuffer::RGBBuffer(uint16_t _width, uint16_t _height) : AbstractBuffer(_width, _height) {
    // initialize channels with all zeros
    redChannel = new uint8_t[((uint32_t)width) * height];   // initialize as all 255
    greenChannel = new uint8_t[((uint32_t)width) * height]; // initialize as all 255
    blueChannel = new uint8_t[((uint32_t)width) * height];  // initialize as all 255
    alphaChannel = new float[((uint32_t)width) * height];   // initialize as all 1s

    for (uint32_t i = 0; i < width * height; i++) {
        redChannel[i] = 255;
    }
    for (uint32_t i = 0; i < width * height; i++) {
        greenChannel[i] = 255;
    }
    for (uint32_t i = 0; i < width * height; i++) {
        blueChannel[i] = 255;
    }
    for (uint32_t i = 0; i < width * height; i++) {
        alphaChannel[i] = 1;
    }
}

RGBBuffer::~RGBBuffer() {
    delete[] redChannel;
    delete[] greenChannel;
    delete[] blueChannel;
}

void RGBBuffer::FillBuffer(uint8_t value) {
    for (int i = 0; i < width * height; i++) {
        redChannel[i] = value;
    }
    for (int i = 0; i < width * height; i++) {
        greenChannel[i] = value;
    }
    for (int i = 0; i < width * height; i++) {
        blueChannel[i] = value;
    }
}

void RGBBuffer::FillBuffer(const ElementStyle& style) {
    for (int i = 0; i < width * height; i++) {
        redChannel[i] = style.redChannel;
    }
    for (int i = 0; i < width * height; i++) {
        greenChannel[i] = style.greenChannel;
    }
    for (int i = 0; i < width * height; i++) {
        blueChannel[i] = style.blueChannel;
    }
    for (int i = 0; i < width * height; i++) {
        alphaChannel[i] = style.alpha;
    }
}

void RGBBuffer::Transform(
    void (&func)(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height), AbstractBuffer& destination
) {
    const RGBBuffer* rgb_destination = dynamic_cast<const RGBBuffer*>(&destination);
    func(redChannel, rgb_destination->redChannel, width, height);
    func(greenChannel, rgb_destination->greenChannel, width, height);
    func(blueChannel, rgb_destination->blueChannel, width, height);
}

AbstractBuffer* RGBBuffer::CreateBufferOfSameType(uint16_t width, uint16_t height) { return new RGBBuffer(width, height); }

void RGBBuffer::CopyBufferFrom(const AbstractBuffer& source) {
    if (source.type() != BufferType::RGBBuffer) {
        throw IncompatibleBufferCopy(this->type(), source.type());
    } else if (source.width != this->width || source.height != this->height) {
        throw MisshapenBufferCopy(source, *this);
    }
    const RGBBuffer* rgb = dynamic_cast<const RGBBuffer*>(&source);
    std::memcpy(this->redChannel, rgb->redChannel, ((uint32_t)width) * height);
    std::memcpy(this->greenChannel, rgb->greenChannel, ((uint32_t)width) * height);
    std::memcpy(this->blueChannel, rgb->blueChannel, ((uint32_t)width) * height);
    std::memcpy(this->alphaChannel, rgb->alphaChannel, width * height);
}

void RGBBuffer::DrawPixel(uint16_t xpos, uint16_t ypos, const ElementStyle& style) {
    if (xpos > width || ypos > height) {
        return;
    }

    uint32_t ypos_32t = ypos;

    redChannel[ypos_32t * width + xpos] =
        utils::BlendPixel(style.redChannel, redChannel[ypos_32t * width + xpos], style.alpha);
    greenChannel[ypos_32t * width + xpos] =
        utils::BlendPixel(style.greenChannel, greenChannel[ypos_32t * width + xpos], style.alpha);
    blueChannel[ypos_32t * width + xpos] =
        utils::BlendPixel(style.blueChannel, blueChannel[ypos_32t * width + xpos], style.alpha);
    alphaChannel[ypos_32t * width + xpos] = utils::BlendAlpha(style.alpha, alphaChannel[ypos_32t * width + xpos]);
}

void RGBBuffer::DrawBitmap(
    uint16_t xpos,
    uint16_t ypos,
    uint16_t width,
    uint16_t height,
    const ElementStyle& backgroundStyle,
    const ElementStyle& foregroundStyle,
    const uint8_t* bitmap
) {
    for (int j = 0; j < height; j++) {
        uint16_t bufferYpos = std::min<uint16_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint16_t bufferXpos = std::min<uint16_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                redChannel[bufferpos] =
                    utils::BlendPixel(foregroundStyle.redChannel, redChannel[bufferpos], foregroundStyle.alpha);
            } else {
                redChannel[bufferpos] =
                    utils::BlendPixel(backgroundStyle.redChannel, redChannel[bufferpos], backgroundStyle.alpha);
                ;
            }
        }
    }
    for (int j = 0; j < height; j++) {
        uint16_t bufferYpos = std::min<uint16_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint16_t bufferXpos = std::min<uint16_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                greenChannel[bufferpos] =
                    utils::BlendPixel(foregroundStyle.greenChannel, greenChannel[bufferpos], foregroundStyle.alpha);
            } else {
                greenChannel[bufferpos] =
                    utils::BlendPixel(backgroundStyle.greenChannel, greenChannel[bufferpos], backgroundStyle.alpha);
                ;
            }
        }
    }
    for (int j = 0; j < height; j++) {
        uint16_t bufferYpos = std::min<uint16_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint16_t bufferXpos = std::min<uint16_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                blueChannel[bufferpos] =
                    utils::BlendPixel(foregroundStyle.blueChannel, blueChannel[bufferpos], foregroundStyle.alpha);
            } else {
                blueChannel[bufferpos] =
                    utils::BlendPixel(backgroundStyle.blueChannel, blueChannel[bufferpos], backgroundStyle.alpha);
                ;
            }
        }
    }
    for (int j = 0; j < height; j++) {
        uint16_t bufferYpos = std::min<uint16_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint16_t bufferXpos = std::min<uint16_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                alphaChannel[bufferpos] = utils::BlendAlpha(foregroundStyle.alpha, alphaChannel[bufferpos]);
            } else {
                alphaChannel[bufferpos] = utils::BlendAlpha(backgroundStyle.alpha, alphaChannel[bufferpos]);
            }
        }
    }
}

void RGBBuffer::DrawRectangle(uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style) {
    // draw top parts of the rectangle
    DrawLine(xpos, ypos, xpos + width, ypos, style);                                  // top edge
    DrawLine(xpos, ypos + height - 1, xpos + width, ypos + height - 1, style);        // bottom edge
    DrawLine(xpos, ypos + 1, xpos, ypos + height - 1, style);                         // left edge
    DrawLine(xpos + width - 1, ypos + 1, xpos + width - 1, ypos + height - 1, style); // right edge
}

void RGBBuffer::DrawFilledRectangle(
    uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style
) {
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = redChannel[this->width * j + i];
            redChannel[this->width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
        }
    }
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = greenChannel[this->width * j + i];
            greenChannel[this->width * j + i] = utils::BlendPixel(style.greenChannel, val, style.alpha);
        }
    }
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = blueChannel[this->width * j + i];
            blueChannel[this->width * j + i] = utils::BlendPixel(style.blueChannel, val, style.alpha);
        }
    }
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = alphaChannel[this->width * j + i];
            alphaChannel[this->width * j + i] = utils::BlendAlpha(style.alpha, val);
        }
    }
}

void RGBBuffer::DrawLine(uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style) {
    // deal with the edge case where it's just a vertical line
    if (xpos_1 == xpos_2) {
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = redChannel[this->width * j + xpos_1];
            redChannel[this->width * j + xpos_1] = utils::BlendPixel(style.redChannel, val, style.alpha);
        }
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = greenChannel[this->width * j + xpos_1];
            greenChannel[this->width * j + xpos_1] = utils::BlendPixel(style.greenChannel, val, style.alpha);
        }
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = blueChannel[this->width * j + xpos_1];
            blueChannel[this->width * j + xpos_1] = utils::BlendPixel(style.blueChannel, val, style.alpha);
        }
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = alphaChannel[this->width * j + xpos_1];
            alphaChannel[this->width * j + xpos_1] = utils::BlendAlpha(style.alpha, val);
        }
        return;
    }

    // calculate slope
    float slope = (ypos_2 - ypos_1) / ((float)(xpos_2 - xpos_1));

    uint32_t j;

    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = redChannel[this->width * j + i];
        redChannel[this->width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
    }
    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = greenChannel[this->width * j + i];
        greenChannel[this->width * j + i] = utils::BlendPixel(style.greenChannel, val, style.alpha);
    }
    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = blueChannel[this->width * j + i];
        blueChannel[this->width * j + i] = utils::BlendPixel(style.blueChannel, val, style.alpha);
    }
    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = alphaChannel[this->width * j + i];
        alphaChannel[this->width * j + i] = utils::BlendAlpha(style.alpha, val);
    }
}

void RGBBuffer::ConvertTo4Color(uint8_t* dest, int memoryWidth, utils::SupportedPalette palette) {
    memset(dest, 0, height * memoryWidth);

    // Iterate through the pixels in the RGB buffer
    for (uint16_t y = 0; y < height; ++y) {
        for (uint16_t x = 0; x < width; ++x) {
            // Calculate the index of the current pixel
            size_t pixelIndex = y * width + x;

            // Retrieve the R, G, B values
            uint8_t r = redChannel[pixelIndex];
            uint8_t g = greenChannel[pixelIndex];
            uint8_t b = blueChannel[pixelIndex];

            // tells us the index of the nearest color to the current pixel
            // black = 0
            // white = 1
            // yellow = 2
            // red = 3
            auto colorIndex = palette.GetNearestColor(r, g, b);

            // Pack the color index into the destination buffer
            size_t byteIndex = pixelIndex / 4;             // 4 pixels per byte
            size_t bitOffset = (3 - (pixelIndex % 4)) * 2; // Determine the bit position

            // // dest[byteIndex] &= ~(0x03 << bitOffset);      // Clear the 2 bits
            dest[byteIndex] |= (colorIndex << bitOffset); // Set the 2 bits
        }
    }
}

void RGBBuffer::ConvertTo6Color(uint8_t* dest, int memoryWidth, utils::SupportedPalette palette) {
    size_t pixelCount = height * memoryWidth;
    memset(dest, 0, pixelCount);

    for (size_t i = 0; i < width * height; i += 1) {
        // Fetch RGB values for two pixels
        uint8_t r = redChannel[i];
        uint8_t g = greenChannel[i];
        uint8_t b = blueChannel[i];

        // Map the first pixel to an indexed color
        uint8_t colorIndex = palette.GetNearestColor(r, g, b);

        size_t byteIndex = i / 2;                // 2 pixels per byte
        size_t bitOffset = (i % 2 == 0) ? 4 : 0; // Determine the bit position

        // // dest[byteIndex] &= ~(0x03 << bitOffset);      // Clear the 2 bits
        dest[byteIndex] |= (colorIndex << bitOffset); // Set the 4 bits
    }
}

void RGBBuffer::ConvertTo7Color(uint8_t* dest, int memoryWidth, utils::SupportedPalette palette) {
    size_t pixelCount = height * memoryWidth;
    memset(dest, 0, pixelCount);

    for (size_t i = 0; i < width * height; i += 1) {
        // Fetch RGB values for two pixels
        uint8_t r = redChannel[i];
        uint8_t g = greenChannel[i];
        uint8_t b = blueChannel[i];

        // Map the first pixel to an indexed color
        uint8_t colorIndex = palette.GetNearestColor(r, g, b);

        size_t byteIndex = i / 2;                // 2 pixels per byte
        size_t bitOffset = (i % 2 == 0) ? 4 : 0; // Determine the bit position

        // // dest[byteIndex] &= ~(0x03 << bitOffset);      // Clear the 2 bits
        dest[byteIndex] |= (colorIndex << bitOffset); // Set the 4 bits
    }
}

void RGBBuffer::DrawBuffer(uint16_t xpos, uint16_t ypos, const AbstractBuffer& buffer) {
    auto& b = static_cast<const RGBBuffer&>(buffer);

    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.redChannel[b.width * j + i];
                    uint8_t alpha = b.alphaChannel[b.width * j + i];
                    redChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendPixel(val, this->redChannel[this->width * (ypos + j) + (xpos + i)], alpha);
                }
            }
        }
    }
    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.greenChannel[b.width * j + i];
                    uint8_t alpha = b.alphaChannel[b.width * j + i];
                    greenChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendPixel(val, this->greenChannel[this->width * (ypos + j) + (xpos + i)], alpha);
                }
            }
        }
    }
    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.blueChannel[b.width * j + i];
                    uint8_t alpha = b.alphaChannel[b.width * j + i];
                    blueChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendPixel(val, this->blueChannel[this->width * (ypos + j) + (xpos + i)], alpha);
                }
            }
        }
    }
    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.alphaChannel[b.width * j + i];
                    alphaChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendAlpha(val, alphaChannel[this->width * (ypos + j) + (xpos + i)]);
                }
            }
        }
    }
}

RedBlackBuffer::RedBlackBuffer(uint16_t _width, uint16_t _height) : AbstractBuffer(_width, _height) {
    // initialize channels with all zeros
    redChannel = new uint8_t[((uint32_t)width) * height]();
    blackChannel = new uint8_t[((uint32_t)width) * height]();
}

RedBlackBuffer::~RedBlackBuffer() {
    delete[] redChannel;
    delete[] blackChannel;
}

void RedBlackBuffer::FillBuffer(uint8_t value) {
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = value;
    }
    // only set black channel
    for (int i = 0; i < width * height; i++) {
        redChannel[i] = 0;
    }
}

void RedBlackBuffer::FillBuffer(const ElementStyle& style) {
    for (int i = 0; i < width * height; i++) {
        redChannel[i] = style.redChannel;
    }
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = style.blackChannel;
    }
    for (int i = 0; i < width * height; i++) {
        alphaChannel[i] = style.alpha;
    }
}

void RedBlackBuffer::Transform(
    void (&func)(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height), AbstractBuffer& destination
) {
    const RedBlackBuffer* rgb_destination = dynamic_cast<const RedBlackBuffer*>(&destination);
    func(redChannel, rgb_destination->redChannel, width, height);
    func(blackChannel, rgb_destination->blackChannel, width, height);
}

AbstractBuffer* RedBlackBuffer::CreateBufferOfSameType(uint16_t width, uint16_t height) {
    return new RedBlackBuffer(width, height);
}

void RedBlackBuffer::CopyBufferFrom(const AbstractBuffer& source) {
    if (source.type() != BufferType::RedBlackBuffer) {
        throw IncompatibleBufferCopy(this->type(), source.type());
    } else if (source.width != this->width || source.height != this->height) {
        throw MisshapenBufferCopy(source, *this);
    }
    const RedBlackBuffer* rgb = dynamic_cast<const RedBlackBuffer*>(&source);
    std::memcpy(this->redChannel, rgb->redChannel, ((uint32_t)width) * height);
    std::memcpy(this->blackChannel, rgb->blackChannel, ((uint32_t)width) * height);
    std::memcpy(this->alphaChannel, rgb->alphaChannel, width * height);
}

void RedBlackBuffer::DrawPixel(uint16_t xpos, uint16_t ypos, const ElementStyle& style) {
    if (xpos > width || ypos > height) {
        return;
    }

    uint32_t ypos_32t = ypos;

    blackChannel[ypos_32t * width + xpos] =
        utils::BlendPixel(style.blackChannel, blackChannel[ypos_32t * width + xpos], style.alpha);
    redChannel[ypos_32t * width + xpos] =
        utils::BlendPixel(style.redChannel, redChannel[ypos_32t * width + xpos], style.alpha);
    alphaChannel[ypos_32t * width + xpos] = utils::BlendAlpha(style.alpha, alphaChannel[ypos_32t * width + xpos]);
}

void RedBlackBuffer::DrawBitmap(
    uint16_t xpos,
    uint16_t ypos,
    uint16_t width,
    uint16_t height,
    const ElementStyle& backgroundStyle,
    const ElementStyle& foregroundStyle,
    const uint8_t* bitmap
) {
    for (int j = 0; j < height; j++) {
        uint16_t bufferYpos = std::min<uint16_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint16_t bufferXpos = std::min<uint16_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                alphaChannel[bufferpos] = utils::BlendAlpha(foregroundStyle.alpha, alphaChannel[bufferpos]);
            } else {
                alphaChannel[bufferpos] = utils::BlendAlpha(backgroundStyle.alpha, alphaChannel[bufferpos]);
            }
        }
    }
    for (int j = 0; j < height; j++) {
        uint32_t bufferYpos = std::min<uint32_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint32_t bufferXpos = std::min<uint32_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                redChannel[bufferpos] =
                    utils::BlendPixel(foregroundStyle.redChannel, redChannel[bufferpos], foregroundStyle.alpha);
            } else {
                redChannel[bufferpos] =
                    utils::BlendPixel(backgroundStyle.redChannel, redChannel[bufferpos], backgroundStyle.alpha);
                ;
            }
        }
    }
    for (int j = 0; j < height; j++) {
        uint32_t bufferYpos = std::min<uint32_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint32_t bufferXpos = std::min<uint32_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                blackChannel[bufferpos] =
                    utils::BlendPixel(foregroundStyle.blackChannel, blackChannel[bufferpos], foregroundStyle.alpha);
            } else {
                blackChannel[bufferpos] =
                    utils::BlendPixel(backgroundStyle.blackChannel, blackChannel[bufferpos], backgroundStyle.alpha);
                ;
            }
        }
    }
}

void RedBlackBuffer::DrawRectangle(
    uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style
) {
    // draw top parts of the rectangle
    DrawLine(xpos, ypos, xpos + width, ypos, style);                                  // top edge
    DrawLine(xpos, ypos + height - 1, xpos + width, ypos + height - 1, style);        // bottom edge
    DrawLine(xpos, ypos + 1, xpos, ypos + height - 1, style);                         // left edge
    DrawLine(xpos + width - 1, ypos + 1, xpos + width - 1, ypos + height - 1, style); // right edge
}

void RedBlackBuffer::DrawFilledRectangle(
    uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style
) {
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = blackChannel[this->width * j + i];
            blackChannel[this->width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
        }
    }
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = redChannel[this->width * j + i];
            redChannel[this->width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
        }
    }
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = alphaChannel[this->width * j + i];
            alphaChannel[this->width * j + i] = utils::BlendAlpha(style.alpha, val);
        }
    }
}

void RedBlackBuffer::DrawLine(
    uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style
) {
    // deal with the edge case where it's just a vertical line
    if (xpos_1 == xpos_2) {
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = blackChannel[this->width * j + xpos_1];
            blackChannel[this->width * j + xpos_1] = utils::BlendPixel(style.blackChannel, val, style.alpha);
        }
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = redChannel[this->width * j + xpos_1];
            redChannel[this->width * j + xpos_1] = utils::BlendPixel(style.redChannel, val, style.alpha);
        }
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = alphaChannel[this->width * j + xpos_1];
            alphaChannel[this->width * j + xpos_1] = utils::BlendAlpha(style.alpha, val);
        }
        return;
    }

    // calculate slope
    float slope = (ypos_2 - ypos_1) / ((float)(xpos_2 - xpos_1));

    uint32_t j;

    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = blackChannel[this->width * j + i];
        blackChannel[this->width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
    }
    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = redChannel[this->width * j + i];
        redChannel[this->width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
    }
    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = alphaChannel[this->width * j + i];
        alphaChannel[this->width * j + i] = utils::BlendAlpha(style.alpha, val);
    }
}

void RedBlackBuffer::ConvertTo1Bit(uint8_t* dest_black, uint8_t* dest_red) {
    uint16_t packedBytesWidth = width % 8 == 0 ? width / 8 : width / 8 + 1;
    memset(dest_black, 0, height * packedBytesWidth);
    memset(dest_red, 0, height * packedBytesWidth);

    uint32_t verticalPos = 0;

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            // pack 8 pixels into 1 byte
            auto val = blackChannel[y * width + x];
            if (val == 255) {
                dest_black[verticalPos + (x / 8)] |= (1 << (7 - (x % 8))); // write 1
            } else {
                dest_black[verticalPos + (x / 8)] &= ~(1 << (7 - (x % 8))); // write 0
            }
        }
        verticalPos += packedBytesWidth;
    }

    verticalPos = 0;

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            // pack 8 pixels into 1 byte
            auto val = redChannel[y * width + x];
            if (val == 255) {
                dest_red[verticalPos + (x / 8)] |= (1 << (7 - (x % 8))); // write 1
            } else {
                dest_red[verticalPos + (x / 8)] &= ~(1 << (7 - (x % 8))); // write 0
            }
        }
        verticalPos += packedBytesWidth;
    }
}

void RedBlackBuffer::DrawBuffer(uint16_t xpos, uint16_t ypos, const AbstractBuffer& buffer) {
    auto& b = static_cast<const RedBlackBuffer&>(buffer);

    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.redChannel[b.width * j + i];
                    uint8_t alpha = b.alphaChannel[b.width * j + i];
                    redChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendPixel(val, this->redChannel[this->width * (ypos + j) + (xpos + i)], alpha);
                }
            }
        }
    }
    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.blackChannel[b.width * j + i];
                    uint8_t alpha = b.alphaChannel[b.width * j + i];
                    blackChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendPixel(val, this->blackChannel[this->width * (ypos + j) + (xpos + i)], alpha);
                }
            }
        }
    }
    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.alphaChannel[b.width * j + i];
                    alphaChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendAlpha(val, alphaChannel[this->width * (ypos + j) + (xpos + i)]);
                }
            }
        }
    }
}

GrayscaleBuffer::GrayscaleBuffer(uint16_t _width, uint16_t _height) : AbstractBuffer(_width, _height) {
    blackChannel = new uint8_t[width * height];
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = 255;
    }
}

GrayscaleBuffer::~GrayscaleBuffer() { delete[] blackChannel; }

void GrayscaleBuffer::FillBuffer(uint8_t value) {
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = value;
    }
}

void GrayscaleBuffer::FillBuffer(const ElementStyle& style) {
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = style.blackChannel;
    }
    for (int i = 0; i < width * height; i++) {
        alphaChannel[i] = style.alpha;
    }
}

void GrayscaleBuffer::Transform(
    void (&func)(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height), AbstractBuffer& destination
) {
    const GrayscaleBuffer* rgb_destination = dynamic_cast<const GrayscaleBuffer*>(&destination);
    func(blackChannel, rgb_destination->blackChannel, width, height);
}

AbstractBuffer* GrayscaleBuffer::CreateBufferOfSameType(uint16_t width, uint16_t height) {
    return new GrayscaleBuffer(width, height);
}

void GrayscaleBuffer::CopyBufferFrom(const AbstractBuffer& source) {
    if (source.type() != BufferType::GrayscaleBuffer) {
        throw IncompatibleBufferCopy(this->type(), source.type());
    } else if (source.width != this->width || source.height != this->height) {
        throw MisshapenBufferCopy(source, *this);
    }
    const GrayscaleBuffer* rgb = dynamic_cast<const GrayscaleBuffer*>(&source);
    std::memcpy(this->blackChannel, rgb->blackChannel, width * height);
    std::memcpy(this->alphaChannel, rgb->alphaChannel, width * height);
}

void GrayscaleBuffer::DrawPixel(uint16_t xpos, uint16_t ypos, const ElementStyle& style) {
    if (xpos > width || ypos > height) {
        return;
    }

    blackChannel[ypos * width + xpos] =
        utils::BlendPixel(style.blackChannel, blackChannel[ypos * width + xpos], style.alpha);
    alphaChannel[ypos * width + xpos] = utils::BlendAlpha(style.alpha, alphaChannel[ypos * width + xpos]);
}

void GrayscaleBuffer::DrawBitmap(
    uint16_t xpos,
    uint16_t ypos,
    uint16_t width,
    uint16_t height,
    const ElementStyle& backgroundStyle,
    const ElementStyle& foregroundStyle,
    const uint8_t* bitmap
) {
    for (int j = 0; j < height; j++) {
        uint16_t bufferYpos = std::min<uint16_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint16_t bufferXpos = std::min<uint16_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                alphaChannel[bufferpos] = utils::BlendAlpha(foregroundStyle.alpha, alphaChannel[bufferpos]);
            } else {
                alphaChannel[bufferpos] = utils::BlendAlpha(backgroundStyle.alpha, alphaChannel[bufferpos]);
            }
        }
    }
    for (int j = 0; j < height; j++) {
        uint16_t bufferYpos = std::min<uint16_t>(ypos + j, this->height);
        for (int i = 0; i < width; i++) {
            uint16_t bufferXpos = std::min<uint16_t>(xpos + i, this->width);
            bool val = getPixel(bitmap, width, i, j);
            uint32_t bufferpos = bufferYpos * this->width + bufferXpos;
            if (val) {
                blackChannel[bufferpos] =
                    utils::BlendPixel(foregroundStyle.blackChannel, blackChannel[bufferpos], foregroundStyle.alpha);
            } else {
                blackChannel[bufferpos] =
                    utils::BlendPixel(backgroundStyle.blackChannel, blackChannel[bufferpos], backgroundStyle.alpha);
            }
        }
    }
}

void GrayscaleBuffer::DrawRectangle(
    uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style
) {
    // draw top parts of the rectangle
    DrawLine(xpos, ypos, xpos + width, ypos, style);                                  // top edge
    DrawLine(xpos, ypos + height - 1, xpos + width, ypos + height - 1, style);        // bottom edge
    DrawLine(xpos, ypos + 1, xpos, ypos + height - 1, style);                         // left edge
    DrawLine(xpos + width - 1, ypos + 1, xpos + width - 1, ypos + height - 1, style); // right edge
}

void GrayscaleBuffer::DrawFilledRectangle(
    uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style
) {
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = blackChannel[this->width * j + i];
            blackChannel[this->width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
        }
    }
    for (uint32_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint32_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = alphaChannel[this->width * j + i];
            alphaChannel[this->width * j + i] = utils::BlendAlpha(style.alpha, val);
        }
    }
}

void GrayscaleBuffer::DrawLine(
    uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style
) {
    // deal with the edge case where it's just a vertical line
    if (xpos_1 == xpos_2) {
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = blackChannel[this->width * j + xpos_1];
            blackChannel[this->width * j + xpos_1] = utils::BlendPixel(style.blackChannel, val, style.alpha);
        }
        for (uint32_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = alphaChannel[this->width * j + xpos_1];
            alphaChannel[this->width * j + xpos_1] = utils::BlendAlpha(style.alpha, val);
        }

        return;
    }

    // calculate slope
    float slope = (ypos_2 - ypos_1) / ((float)(xpos_2 - xpos_1));

    uint16_t j;

    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = blackChannel[this->width * j + i];
        blackChannel[this->width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
    }
    for (uint32_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = alphaChannel[this->width * j + i];
        alphaChannel[this->width * j + i] = utils::BlendAlpha(style.alpha, val);
    }
}

void GrayscaleBuffer::ConvertTo1Bit(uint8_t* dest) {
    uint16_t packedBytesWidth = width % 8 == 0 ? width / 8 : width / 8 + 1;
    memset(dest, 0, height * packedBytesWidth);

    uint32_t verticalPos = 0;

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            // pack 8 pixels into 1 byte
            auto val = blackChannel[y * width + x];
            if (val == 255) {
                dest[verticalPos + (x / 8)] |= (1 << (7 - (x % 8))); // write 1
            } else {
                dest[verticalPos + (x / 8)] &= ~(1 << (7 - (x % 8))); // write 0
            }
        }
        verticalPos += packedBytesWidth;
    }
}

void GrayscaleBuffer::ConvertTo2Bit(uint8_t* dest) {
    uint16_t packedBytesWidth = width % 4 == 0 ? width / 4 : width / 4 + 1;
    memset(dest, 0, height * packedBytesWidth);

    uint32_t verticalPos = 0;

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            auto val = blackChannel[y * width + x];
            int shift = 6 - ((x % 4) * 2); // Determine which pair of bits to modify
            if (val < 64) {
                dest[verticalPos + (x / 4)] |= (0b11 << shift); // Black
            } else if (val < 128) {
                dest[verticalPos + (x / 4)] |= (0b10 << shift); // Dark Gray
            } else if (val < 192) {
                dest[verticalPos + (x / 4)] |= (0b01 << shift); // Light Gray
            } else {
                dest[verticalPos + (x / 4)] |= (0b00 << shift); // White (clear bits)
            }
        }
        verticalPos += packedBytesWidth;
    }
}

void GrayscaleBuffer::DrawBuffer(uint16_t xpos, uint16_t ypos, const AbstractBuffer& buffer) {
    auto& b = static_cast<const GrayscaleBuffer&>(buffer);

    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.blackChannel[b.width * j + i];
                    uint8_t alpha = b.alphaChannel[b.width * j + i];
                    blackChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendPixel(val, this->blackChannel[this->width * (ypos + j) + (xpos + i)], alpha);
                }
            }
        }
    }
    for (uint32_t j = 0; j < b.height; j++) {
        if (ypos + j > this->height) {
            break;
        } else {
            for (uint32_t i = 0; i < b.width; i++) {
                if (xpos + i > this->width) {
                    break;
                } else {
                    uint8_t val = b.alphaChannel[b.width * j + i];
                    alphaChannel[this->width * (ypos + j) + (xpos + i)] =
                        utils::BlendAlpha(val, alphaChannel[this->width * (ypos + j) + (xpos + i)]);
                }
            }
        }
    }
}

} // namespace epaperapi