#include "wsepaperapi.h"
#include "bufferutils.h"

#include <iostream>

using namespace std;

namespace epaperapi {
void Renderer::RegenerateBuffer() {
    if (transformation == BufferTransform::None) {
        // clear the old buffer values
        tempBuffer.FillBuffer(255); // fill with white color

        for (AbstractElement* elem : elements) {
            if (elem->visible) {
                elem->Draw(tempBuffer);
            }
        }
    } else {
        // Because we need to apply a transformation, first Draw each element to the intermediate buffer and then
        // we can apply transformation.

        intermediateBuffer->FillBuffer(255); // fill with white color

        for (AbstractElement* elem : elements) {
            if (elem->visible) {
                elem->Draw(*intermediateBuffer);
            }
        }

        utils::TransformBuffer(*intermediateBuffer, tempBuffer, transformation);
    }
}
void Renderer::Refresh(RefreshMode mode, bool regenerateBuffer) {

    if (regenerateBuffer) {
        RegenerateBuffer();
    }

    drawTarget.Refresh(mode);
}

void Renderer::SetTransformation(BufferTransform _transformation) {
    if (intermediateBuffer != nullptr) {
        delete intermediateBuffer;
        intermediateBuffer = nullptr;
    }

    transformation = _transformation;

    if (transformation == BufferTransform::None) {
        // Do nothing
    } else if (transformation == BufferTransform::Rotate90Clockwise ||
               transformation == BufferTransform::Rotate90CounterClockwise) {
        // Create a new buffer with the height and width of the DrawTarget reversed
        intermediateBuffer = tempBuffer.CreateBufferOfSameType(tempBuffer.height, tempBuffer.width);
    } else if (transformation == BufferTransform::Rotate180) {
        // we still need an intermediate buffer but the height and width don't have to be reversed
        intermediateBuffer = tempBuffer.CreateBufferOfSameType(tempBuffer.width, tempBuffer.height);
    }
}

Renderer::~Renderer() {
    if (intermediateBuffer != nullptr) {
        delete intermediateBuffer;
    }
}

} // namespace epaperapi