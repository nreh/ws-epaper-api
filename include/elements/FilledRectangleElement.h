#include "../elements.h"

namespace epaperapi::elements {

/// @brief A simple filled rectangle
class FilledRectangleElement : public AbstractElement {
  public:
    uint16_t width, height;

    FilledRectangleElement(uint16_t width, uint16_t height) : width(width), height(height) {}
    FilledRectangleElement(uint16_t width, uint16_t height, uint16_t xpos, uint16_t ypos)
        : width(width), height(height), AbstractElement(xpos, ypos) {}

    /// @brief Draw the FilledRectangle to the target buffer
    /// @param target Buffer that this Filled Rectangle will be Drawn on to
    void Draw(AbstractBuffer& target) override {
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

            for (int j = ypos; j < height; j++) {
                for (int i = xpos; i < width; i++) {
                    unsigned char val = rblk->redChannel[target.width * j + i];
                    rblk->redChannel[width * j + i] = utils::BlendPixel(style.redChannel, val, style.alpha);
                }
            }
            for (int j = ypos; j < height; j++) {
                for (int i = xpos; i < width; i++) {
                    unsigned char val = rblk->redChannel[target.width * j + i];
                    rblk->blackChannel[width * j + i] = utils::BlendPixel(style.blackChannel, val, style.alpha);
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
};

} // namespace epaperapi::elements