#include "../bufferutils.h"
#include "../elements.h"
#include <vector>

namespace epaperapi::elements {
/// @brief A `CanvasElement` is like a smaller intermediate buffer (similar to the Renderer) that allows for drawing things
/// once into a bitmap like datastructure before it is rendered. The main advantage of this is that it acts as a container
/// for multiple elements to be drawn which can then be moved around and manipulated together.
///
/// Another advantage is that expensive draw operations will be done only once, the result being stored as just the raw pixel
/// values that can be drawn over and over again without any extra overhead of expensive Draw() functions.
///
/// Another advantage is that it allows for rotation operations that are not typically available on other elements.
///
/// Call the `Refresh()` function to draw elements on the internal buffer whenever they're updated.
class CanvasElement : public AbstractElement {
  protected:
    AbstractBuffer* internalBuffer = nullptr;
    AbstractBuffer* intermediateBuffer =
        nullptr; // if the transformation is not None, then this will be used for applying transformations
    uint16_t width, height;
    BufferTransform transformation = BufferTransform::None;

  public:
    /// @brief Elements to be drawn - positions are relative to the position of the canvas
    std::vector<AbstractElement*> elements;

    ElementStyle backgroundStyle = ElementStyle(255, 255, 255);

    CanvasElement(
        AbstractBuffer& containingBuffer,
        uint16_t xpos,
        uint16_t ypos,
        uint16_t width,
        uint16_t height,
        BufferTransform transformation = BufferTransform::None
    )
        : AbstractElement(xpos, ypos), width(width), height(height), transformation(transformation) {

        if (transformation == BufferTransform::None) {
            internalBuffer = containingBuffer.CreateBufferOfSameType(width, height);
        } else if (transformation == BufferTransform::Rotate90Clockwise ||
                   transformation == BufferTransform::Rotate90CounterClockwise) {
            internalBuffer = containingBuffer.CreateBufferOfSameType(height, width);
            intermediateBuffer = internalBuffer->CreateBufferOfSameType(width, height);
        } else if (transformation == BufferTransform::Rotate180) {
            internalBuffer = containingBuffer.CreateBufferOfSameType(width, height);
            intermediateBuffer = internalBuffer->CreateBufferOfSameType(width, height);
        }

        if (containingBuffer.type() == BufferType::RedBlackBuffer) {
            backgroundStyle = ElementStyle(0, 255);
        }
    }

    CanvasElement(
        BufferType bufferType,
        uint16_t xpos,
        uint16_t ypos,
        uint16_t width,
        uint16_t height,
        BufferTransform transformation = BufferTransform::None
    )
        : AbstractElement(xpos, ypos), width(width), height(height), transformation(transformation) {

        if (transformation == BufferTransform::None) {
            if (bufferType == BufferType::RGBBuffer) {
                internalBuffer = new RGBBuffer(width, height);
            } else if (bufferType == BufferType::RedBlackBuffer) {
                internalBuffer = new RedBlackBuffer(width, height);
            } else if (bufferType == BufferType::GrayscaleBuffer) {
                internalBuffer = new GrayscaleBuffer(width, height);
            }
        } else if (transformation == BufferTransform::Rotate90Clockwise ||
                   transformation == BufferTransform::Rotate90CounterClockwise) {
            if (bufferType == BufferType::RGBBuffer) {
                internalBuffer = new RGBBuffer(height, width);
            } else if (bufferType == BufferType::RedBlackBuffer) {
                internalBuffer = new RedBlackBuffer(height, width);
            } else if (bufferType == BufferType::GrayscaleBuffer) {
                internalBuffer = new GrayscaleBuffer(height, width);
            }
            intermediateBuffer = internalBuffer->CreateBufferOfSameType(width, height);
        } else if (transformation == BufferTransform::Rotate180) {
            if (bufferType == BufferType::RGBBuffer) {
                internalBuffer = new RGBBuffer(width, height);
            } else if (bufferType == BufferType::RedBlackBuffer) {
                internalBuffer = new RedBlackBuffer(width, height);
            } else if (bufferType == BufferType::GrayscaleBuffer) {
                internalBuffer = new GrayscaleBuffer(width, height);
            }
            intermediateBuffer = internalBuffer->CreateBufferOfSameType(width, height);
        }

        if (bufferType == BufferType::RedBlackBuffer) {
            backgroundStyle = ElementStyle(0, 255);
        }
    }

    ~CanvasElement() {
        if (internalBuffer != nullptr) {
            delete internalBuffer;
        }
        if (intermediateBuffer != nullptr) {
            delete intermediateBuffer;
        }
    }

    void AddElement(AbstractElement* element) { elements.push_back(element); }
    void Draw(AbstractBuffer& target) override { target.DrawBuffer(xpos, ypos, *internalBuffer); }
    void Refresh() {
        if (transformation == BufferTransform::None) {
            // clear the old buffer values
            internalBuffer->FillBuffer(backgroundStyle);

            for (AbstractElement* elem : elements) {
                if (elem->visible) {
                    elem->Draw(*internalBuffer);
                }
            }
        } else {
            // Because we need to apply a transformation, first Draw each element to the intermediate buffer and then
            // we can apply transformation.

            intermediateBuffer->FillBuffer(backgroundStyle);

            for (AbstractElement* elem : elements) {
                if (elem->visible) {
                    elem->Draw(*intermediateBuffer);
                }
            }

            utils::TransformBuffer(*intermediateBuffer, *internalBuffer, transformation);
        }
    }
};
} // namespace epaperapi::elements