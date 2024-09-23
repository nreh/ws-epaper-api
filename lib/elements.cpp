#include "elements.h"
#include "buffers.h"
#include "epaperapi.h"

#include <algorithm>

namespace epaperapi {
FilledRectangleElement::FilledRectangleElement(uint16_t _width, uint16_t _height) : width(_width), height(_height) {}

void FilledRectangleElement::Draw(AbstractBuffer& target) {
    switch (target.type()) {
    case BUFFERTYPE::RGBBuffer: {
        const RGBBuffer* rgb = dynamic_cast<const RGBBuffer*>(&target);

        uint8_t red = style.GetMultipliedRed();
        uint8_t green = style.GetMultipliedGreen();
        uint8_t blue = style.GetMultipliedBlue();

        for (int j = ypos; j < ypos + height && j < target.height; j++) {
            for (int i = xpos; i < xpos + width && i < target.width; i++) {
                rgb->redChannel[target.width * j + i] = red;
            }
        }
        for (int j = ypos; j < ypos + height && j < target.height; j++) {
            for (int i = xpos; i < xpos + width && i < target.width; i++) {
                rgb->greenChannel[target.width * j + i] = green;
            }
        }
        for (int j = ypos; j < ypos + height && j < target.height; j++) {
            for (int i = xpos; i < xpos + width && i < target.width; i++) {
                rgb->blueChannel[target.width * j + i] = blue;
            }
        }

        break;
    }

    case BUFFERTYPE::RedBlackBuffer: {
        const RedBlackBuffer* rblk = dynamic_cast<const RedBlackBuffer*>(&target);

        uint8_t red = style.GetMultipliedRed();
        uint8_t black = style.GetMultipliedBlack();

        for (int j = ypos; j < height; j++) {
            for (int i = xpos; i < width; i++) {
                rblk->redChannel[width * j + i] = red;
            }
        }
        for (int j = ypos; j < height; j++) {
            for (int i = xpos; i < width; i++) {
                rblk->blackChannel[width * j + i] = black;
            }
        }

        break;
    }

    case BUFFERTYPE::GrayscaleBuffer: {
        const GrayscaleBuffer* rblk = dynamic_cast<const GrayscaleBuffer*>(&target);

        uint8_t black = style.GetMultipliedBlack();

        for (int j = ypos; j < height; j++) {
            for (int i = xpos; i < width; i++) {
                rblk->blackChannel[width * j + i] = black;
            }
        }

        break;
    }
    }
}
uint8_t ElementStyle::GetMultipliedRed() { return redChannel * alpha; }
uint8_t ElementStyle::GetMultipliedGreen() { return greenChannel * alpha; }
uint8_t ElementStyle::GetMultipliedBlue() { return blueChannel * alpha; }
uint8_t ElementStyle::GetMultipliedBlack() { return blackChannel * alpha; }
} // namespace epaperapi