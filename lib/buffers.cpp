#include "buffers.h"

#include <algorithm>
#include <cstring>
#include <string>
#include <type_traits>

namespace epaperapi {

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
    if (newValues.type() != BUFFERTYPE::RGBBuffer) {
        throw IncompatibleBufferWrite(this->type(), newValues.type());
    }

    const RGBBuffer* source = dynamic_cast<const RGBBuffer*>(&newValues);

    for (int j = ypos; j < height; j++) {
        for (int i = xpos; i < width; i++) {
            auto newval =
                std::clamp<uint16_t>(source->redChannel[(width * j) + i] * source->alphaChannel[(width * j) + i], 0, 255);
            redChannel[(width * j) + i] = newval;
        }
    }
    for (int j = ypos; j < height; j++) {
        for (int i = xpos; i < width; i++) {
            auto newval =
                std::clamp<uint16_t>(source->greenChannel[(width * j) + i] * source->alphaChannel[(width * j) + i], 0, 255);
            greenChannel[(width * j) + i] = newval;
        }
    }
    for (int j = ypos; j < height; j++) {
        for (int i = xpos; i < width; i++) {
            auto newval =
                std::clamp<uint16_t>(source->blueChannel[(width * j) + i] * source->alphaChannel[(width * j) + i], 0, 255);
            blueChannel[(width * j) + i] = newval;
        }
    }
}

void RGBBuffer::CopyBufferFrom(const AbstractBuffer& source) {
    if (source.type() != BUFFERTYPE::RGBBuffer) {
        throw IncompatibleBufferCopy(this->type(), source.type());
    } else if (source.width != this->width || source.height != this->height) {
        throw MisshapenBufferCopy(source, *this);
    }
    const RGBBuffer* rgb = dynamic_cast<const RGBBuffer*>(&source);
    std::memcpy(this->redChannel, rgb->redChannel, width * height);
    std::memcpy(this->greenChannel, rgb->greenChannel, width * height);
    std::memcpy(this->blueChannel, rgb->blueChannel, width * height);
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
    if (newValues.type() != BUFFERTYPE::RedBlackBuffer) {
        throw IncompatibleBufferWrite(this->type(), newValues.type());
    }

    const RedBlackBuffer* source = dynamic_cast<const RedBlackBuffer*>(&newValues);

    for (int j = ypos; j < height; j++) {
        for (int i = xpos; i < width; i++) {
            auto newval =
                std::clamp<uint16_t>(source->redChannel[(width * j) + i] * source->alphaChannel[(width * j) + i], 0, 255);
            redChannel[(width * j) + i] = newval;
        }
    }
    for (int j = ypos; j < height; j++) {
        for (int i = xpos; i < width; i++) {
            auto newval =
                std::clamp<uint16_t>(source->blackChannel[(width * j) + i] * source->alphaChannel[(width * j) + i], 0, 255);
            blackChannel[(width * j) + i] = newval;
        }
    }
}

void RedBlackBuffer::CopyBufferFrom(const AbstractBuffer& source) {
    if (source.type() != BUFFERTYPE::RedBlackBuffer) {
        throw IncompatibleBufferCopy(this->type(), source.type());
    } else if (source.width != this->width || source.height != this->height) {
        throw MisshapenBufferCopy(source, *this);
    }
    const RedBlackBuffer* rgb = dynamic_cast<const RedBlackBuffer*>(&source);
    std::memcpy(this->redChannel, rgb->redChannel, width * height);
    std::memcpy(this->blackChannel, rgb->blackChannel, width * height);
}

GrayscaleBuffer::GrayscaleBuffer(uint16_t _width, uint16_t _height) : AbstractBuffer(_width, _height) {
    blackChannel = new uint8_t[width * height]();
}

GrayscaleBuffer::~GrayscaleBuffer() { delete[] blackChannel; }

void GrayscaleBuffer::Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) {
    if (newValues.type() != BUFFERTYPE::GrayscaleBuffer) {
        throw IncompatibleBufferWrite(this->type(), newValues.type());
    }

    const GrayscaleBuffer* source = dynamic_cast<const GrayscaleBuffer*>(&newValues);

    for (int j = ypos; j < height; j++) {
        for (int i = xpos; i < width; i++) {
            auto newval =
                std::clamp<uint16_t>(source->blackChannel[(width * j) + i] * source->alphaChannel[(width * j) + i], 0, 255);
            blackChannel[(width * j) + i] = newval;
        }
    }
}

void GrayscaleBuffer::CopyBufferFrom(const AbstractBuffer& source) {
    if (source.type() != BUFFERTYPE::RedBlackBuffer) {
        throw IncompatibleBufferCopy(this->type(), source.type());
    } else if (source.width != this->width || source.height != this->height) {
        throw MisshapenBufferCopy(source, *this);
    }
    const RedBlackBuffer* rgb = dynamic_cast<const RedBlackBuffer*>(&source);
    std::memcpy(this->blackChannel, rgb->blackChannel, width * height);
}

} // namespace epaperapi