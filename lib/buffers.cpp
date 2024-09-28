#include "buffers.h"
#include "utils.h"

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
    blackChannel = new uint8_t[width * height];
    for (int i = 0; i < width * height; i++) {
        blackChannel[i] = 255;
    }
}

GrayscaleBuffer::~GrayscaleBuffer() { delete[] blackChannel; }

void GrayscaleBuffer::Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) {
    if (newValues.type() != BUFFERTYPE::GrayscaleBuffer) {
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

void GrayscaleBuffer::CopyBufferFrom(const AbstractBuffer& source) {
    if (source.type() != BUFFERTYPE::GrayscaleBuffer) {
        throw IncompatibleBufferCopy(this->type(), source.type());
    } else if (source.width != this->width || source.height != this->height) {
        throw MisshapenBufferCopy(source, *this);
    }
    const GrayscaleBuffer* rgb = dynamic_cast<const GrayscaleBuffer*>(&source);
    std::memcpy(this->blackChannel, rgb->blackChannel, width * height);
}

} // namespace epaperapi