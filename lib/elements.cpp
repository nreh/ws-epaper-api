#include "elements.h"
#include "buffers.h"
#include "utils.h"
#include "wsepaperapi.h"

namespace epaperapi {
FilledRectangleElement::FilledRectangleElement(uint16_t _width, uint16_t _height) : width(_width), height(_height) {}

void FilledRectangleElement::Draw(AbstractBuffer& target) {
    switch (target.type()) {
    case BufferType::RGBBuffer: {
        const RGBBuffer* rgb = dynamic_cast<const RGBBuffer*>(&target);

        for (int j = ypos; j < ypos + height && j < target.height; j++) {
            for (int i = xpos; i < xpos + width && i < target.width; i++) {
                unsigned char val = rgb->redChannel[target.width * j + i];
                rgb->redChannel[target.width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
            }
        }
        for (int j = ypos; j < ypos + height && j < target.height; j++) {
            for (int i = xpos; i < xpos + width && i < target.width; i++) {
                unsigned char val = rgb->greenChannel[target.width * j + i];
                rgb->greenChannel[target.width * j + i] = utils::BlendPixel(style.greenChannel, val, style.alpha);
            }
        }
        for (int j = ypos; j < ypos + height && j < target.height; j++) {
            for (int i = xpos; i < xpos + width && i < target.width; i++) {
                unsigned char val = rgb->blueChannel[target.width * j + i];
                rgb->blueChannel[target.width * j + i] = utils::BlendPixel(style.blueChannel, val, style.alpha);
            }
        }

        break;
    }

    case BufferType::RedBlackBuffer: {
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

    case BufferType::GrayscaleBuffer: {
        const GrayscaleBuffer* blk = dynamic_cast<const GrayscaleBuffer*>(&target);

        for (int j = ypos; j < ypos + height && j < target.height; j++) {
            for (int i = xpos; i < xpos + width && i < target.width; i++) {
                unsigned char val = blk->blackChannel[target.width * j + i];
                blk->blackChannel[target.width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
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