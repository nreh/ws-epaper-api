#include "buffers.h"
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
    redChannel = new uint8_t[width * height];   // initialize as all 255
    greenChannel = new uint8_t[width * height]; // initialize as all 255
    blueChannel = new uint8_t[width * height];  // initialize as all 255
    alphaChannel = new float[width * height];   // initialize as all 1s

    for (int i = 0; i < width * height; i++) {
        redChannel[i] = 255;
    }
    for (int i = 0; i < width * height; i++) {
        greenChannel[i] = 255;
    }
    for (int i = 0; i < width * height; i++) {
        blueChannel[i] = 255;
    }
    for (int i = 0; i < width * height; i++) {
        alphaChannel[i] = 1;
    }
}

RGBBuffer::~RGBBuffer() {
    delete[] redChannel;
    delete[] greenChannel;
    delete[] blueChannel;
}

void RGBBuffer::Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) {
    if (newValues.type() != BufferType::RGBBuffer) {
        throw IncompatibleBufferWrite(this->type(), newValues.type());
    }

    const RGBBuffer* rgb = dynamic_cast<const RGBBuffer*>(&newValues);

    unsigned int n = 0;
    for (int j = ypos; j < ypos + rgb->height && j < height; j++) {
        for (int i = xpos; i < xpos + rgb->width && i < width; i++) {
            unsigned char val = rgb->redChannel[width * j + i];
            rgb->redChannel[width * j + i] = utils::BlendPixel(rgb->redChannel[n], val, rgb->alphaChannel[n]);
            n++;
        }
    }

    n = 0;
    for (int j = ypos; j < ypos + rgb->height && j < height; j++) {
        for (int i = xpos; i < xpos + rgb->width && i < width; i++) {
            unsigned char val = rgb->greenChannel[width * j + i];
            rgb->greenChannel[width * j + i] = utils::BlendPixel(rgb->redChannel[n], val, rgb->alphaChannel[n]);
            n++;
        }
    }

    n = 0;
    for (int j = ypos; j < ypos + rgb->height && j < height; j++) {
        for (int i = xpos; i < xpos + rgb->width && i < width; i++) {
            unsigned char val = rgb->blueChannel[width * j + i];
            rgb->blueChannel[width * j + i] = utils::BlendPixel(rgb->redChannel[n], val, rgb->alphaChannel[n]);
            n++;
        }
    }
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
    std::memcpy(this->redChannel, rgb->redChannel, width * height);
    std::memcpy(this->greenChannel, rgb->greenChannel, width * height);
    std::memcpy(this->blueChannel, rgb->blueChannel, width * height);
}

void RGBBuffer::DrawBitmap(
    uint16_t xpos,
    uint16_t ypos,
    uint16_t width,
    uint16_t height,
    const ElementStyle& backgroundStyle,
    const ElementStyle& foregroundStyle,
    const uint8_t* bitmap
) {}

void RGBBuffer::DrawFilledRectangle(
    uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style
) {
    for (uint16_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint16_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = redChannel[this->width * j + i];
            redChannel[this->width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
        }
    }
    for (uint16_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint16_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = greenChannel[this->width * j + i];
            greenChannel[this->width * j + i] = utils::BlendPixel(style.greenChannel, val, style.alpha);
        }
    }
    for (uint16_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint16_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = blueChannel[this->width * j + i];
            blueChannel[this->width * j + i] = utils::BlendPixel(style.blueChannel, val, style.alpha);
        }
    }
}

void RGBBuffer::DrawLine(uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style) {
    // deal with the edge case where it's just a vertical line
    if (xpos_1 == xpos_2) {
        for (uint16_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = redChannel[this->width * j + xpos_1];
            redChannel[this->width * j + xpos_1] = utils::BlendPixel(style.redChannel, val, style.alpha);
        }
        for (uint16_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = greenChannel[this->width * j + xpos_1];
            greenChannel[this->width * j + xpos_1] = utils::BlendPixel(style.greenChannel, val, style.alpha);
        }
        for (uint16_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = blueChannel[this->width * j + xpos_1];
            blueChannel[this->width * j + xpos_1] = utils::BlendPixel(style.blueChannel, val, style.alpha);
        }
        return;
    }

    // calculate slope
    float slope = (ypos_2 - ypos_1) / ((float)(xpos_2 - xpos_1));

    uint16_t j;

    for (uint16_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = redChannel[this->width * j + i];
        redChannel[this->width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
    }
    for (uint16_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = greenChannel[this->width * j + i];
        greenChannel[this->width * j + i] = utils::BlendPixel(style.greenChannel, val, style.alpha);
    }
    for (uint16_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = blueChannel[this->width * j + i];
        blueChannel[this->width * j + i] = utils::BlendPixel(style.blueChannel, val, style.alpha);
    }
}

RedBlackBuffer::RedBlackBuffer(uint16_t _width, uint16_t _height) : AbstractBuffer(_width, _height) {
    // initialize channels with all zeros
    redChannel = new uint8_t[width * height]();
    blackChannel = new uint8_t[width * height]();
}

RedBlackBuffer::~RedBlackBuffer() {
    delete[] redChannel;
    delete[] blackChannel;
}

void RedBlackBuffer::Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) {
    if (newValues.type() != BufferType::RedBlackBuffer) {
        throw IncompatibleBufferWrite(this->type(), newValues.type());
    }

    const RedBlackBuffer* source = dynamic_cast<const RedBlackBuffer*>(&newValues);

    unsigned int n = 0;
    for (int j = ypos; j < ypos + source->height && j < height; j++) {
        for (int i = xpos; i < xpos + source->width && i < width; i++) {
            unsigned char val = source->redChannel[width * j + i];
            source->redChannel[width * j + i] = utils::BlendPixel(source->redChannel[n], val, source->alphaChannel[n]);
            n++;
        }
    }

    n = 0;
    for (int j = ypos; j < ypos + source->height && j < height; j++) {
        for (int i = xpos; i < xpos + source->width && i < width; i++) {
            unsigned char val = source->blackChannel[width * j + i];
            source->blackChannel[width * j + i] = utils::BlendPixel(source->blackChannel[n], val, source->alphaChannel[n]);
            n++;
        }
    }
}

void RedBlackBuffer::FillBuffer(uint8_t value) {
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = value;
    }
    for (int i = 0; i < width * height; i++) {
        redChannel[i] = value;
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
    std::memcpy(this->redChannel, rgb->redChannel, width * height);
    std::memcpy(this->blackChannel, rgb->blackChannel, width * height);
}

void RedBlackBuffer::DrawBitmap(
    uint16_t xpos,
    uint16_t ypos,
    uint16_t width,
    uint16_t height,
    const ElementStyle& backgroundStyle,
    const ElementStyle& foregroundStyle,
    const uint8_t* bitmap
) {}

void RedBlackBuffer::DrawFilledRectangle(
    uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style
) {
    for (uint16_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint16_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = blackChannel[this->width * j + i];
            blackChannel[this->width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
        }
    }
    for (uint16_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint16_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = redChannel[this->width * j + i];
            redChannel[this->width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
        }
    }
}

void RedBlackBuffer::DrawLine(
    uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style
) {
    // deal with the edge case where it's just a vertical line
    if (xpos_1 == xpos_2) {
        for (uint16_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = blackChannel[this->width * j + xpos_1];
            blackChannel[this->width * j + xpos_1] = utils::BlendPixel(style.blackChannel, val, style.alpha);
        }
        for (uint16_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = redChannel[this->width * j + xpos_1];
            redChannel[this->width * j + xpos_1] = utils::BlendPixel(style.redChannel, val, style.alpha);
        }
        return;
    }

    // calculate slope
    float slope = (ypos_2 - ypos_1) / ((float)(xpos_2 - xpos_1));

    uint16_t j;

    for (uint16_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = blackChannel[this->width * j + i];
        blackChannel[this->width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
    }
    for (uint16_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = redChannel[this->width * j + i];
        redChannel[this->width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
    }
}

GrayscaleBuffer::GrayscaleBuffer(uint16_t _width, uint16_t _height) : AbstractBuffer(_width, _height) {
    blackChannel = new uint8_t[width * height];
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = 255;
    }
}

GrayscaleBuffer::~GrayscaleBuffer() { delete[] blackChannel; }

void GrayscaleBuffer::Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) {
    if (newValues.type() != BufferType::GrayscaleBuffer) {
        throw IncompatibleBufferWrite(this->type(), newValues.type());
    }

    const GrayscaleBuffer* source = dynamic_cast<const GrayscaleBuffer*>(&newValues);

    unsigned int n = 0;
    for (int j = ypos; j < ypos + source->height && j < height; j++) {
        for (int i = xpos; i < xpos + source->width && i < width; i++) {
            unsigned char val = source->blackChannel[width * j + i];
            source->blackChannel[width * j + i] = utils::BlendPixel(source->blackChannel[n], val, source->alphaChannel[n]);
            n++;
        }
    }
}

void GrayscaleBuffer::FillBuffer(uint8_t value) {
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = value;
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
            uint16_t bufferpos = bufferYpos * this->width + bufferXpos;
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

void GrayscaleBuffer::DrawFilledRectangle(
    uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style
) {
    for (uint16_t j = ypos; j < ypos + height && j < this->height; j++) {
        for (uint16_t i = xpos; i < xpos + width && i < this->width; i++) {
            uint8_t val = blackChannel[this->width * j + i];
            blackChannel[this->width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
        }
    }
}

void GrayscaleBuffer::DrawLine(
    uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style
) {
    // deal with the edge case where it's just a vertical line
    if (xpos_1 == xpos_2) {
        for (uint16_t j = ypos_1; j < ypos_2 && j < this->height; j++) {
            uint8_t val = blackChannel[this->width * j + xpos_1];
            blackChannel[this->width * j + xpos_1] = utils::BlendPixel(style.blackChannel, val, style.alpha);
        }

        return;
    }

    // calculate slope
    float slope = (ypos_2 - ypos_1) / ((float)(xpos_2 - xpos_1));

    uint16_t j;

    for (uint16_t i = xpos_1; i < xpos_2 && i < this->width; i++) {
        j = slope * i + ypos_1;
        uint8_t val = blackChannel[this->width * j + i];
        blackChannel[this->width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
    }
}

} // namespace epaperapi