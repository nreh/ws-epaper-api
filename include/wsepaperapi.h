#pragma once

/// @brief The base ws-epaper-api namespace
namespace epaperapi {}

#include "buffers.h"
#include "bufferutils.h"
#include "debug.h"
#include "elements.h"

#include <stdint.h>
#include <vector>

namespace epaperapi {

/// @brief Indicates how the display should be refreshed. When in doubt, use Normal.
enum RefreshMode { Normal = 0, Partial = 1 };

/// @brief Abstract class representing something that can be drawn on. Usually an E-Paper display but can also be a virtual
/// display for testing.
class AbstractDrawTarget {
  public:
    /// @brief The width of the DrawTarget in pixels
    const uint16_t width;

    /// @brief The height of the DrawTarget in pixels
    const uint16_t height;

    /// @brief Contains pixels that are currently being displayed. Useful for partial refreshes where we need the old pixel
    /// values.
    AbstractBuffer& buffer;

    /// @brief Refresh the display, showing the contents of the buffer.
    virtual void Refresh(int mode) = 0;

    /// @brief Clear the display to white
    virtual void Clear() = 0;

    AbstractDrawTarget(AbstractBuffer& _buffer) : buffer(_buffer), width(_buffer.width), height(_buffer.height) {}
};

/// @brief Handles draw calls to the draw target as well as holding a list of all elements to be drawn.
class Renderer {
  private:
    /// @brief Our elements are drawn onto this buffer before being sent to the draw target.
    AbstractBuffer& tempBuffer;

    /// @brief Sometimes the buffer will need to have some transformation applied to it before sending to the drawtarget.
    /// Those transformations are first done here and then sent to tempBuffer.
    AbstractBuffer* intermediateBuffer = nullptr;

    BufferTransform transformation = BufferTransform::None;

  public:
    /// @brief List of Elements that are to be drawn
    std::vector<AbstractElement*> elements;

    /// @brief Draw target that visible elements will be drawn on
    AbstractDrawTarget& drawTarget;

    /// @brief Create a new renderer which draws to a drawtarget
    /// @param _drawTarget DrawTarget to draw to, typically a physical E-Paper display
    /// @param transformation Perform a transformation on the buffer before being sent to the
    /// DrawTarget. Useful if your display is physically rotated and you want your coordinate system to reflect that.
    Renderer(AbstractDrawTarget& _drawTarget, BufferTransform transformation = BufferTransform::None)
        : drawTarget(_drawTarget), tempBuffer(_drawTarget.buffer) {
        SetTransformation(transformation); // intermediateBuffer is also created here
    }

    /// @brief Go through all visible Elements and draw them onto the buffer.
    void RegenerateBuffer();

    /// @brief Draw all visible elements onto the draw target
    /// @param mode How the display should be refreshed
    /// @param regenerateBuffer If true, all visible elements have their Draw() function called and the buffer is
    /// regenerated. You can disble this if you know no changes have been made to the elements.
    void Refresh(int mode = RefreshMode::Normal, bool regenerateBuffer = true);

    /// @brief Change what transformation is performed on the buffer before being set to the DrawTarget. Useful if your
    /// display is physically rotated and you want your coordinate system to reflect that.
    /// @param _transformation
    void SetTransformation(BufferTransform _transformation);

    ~Renderer();
};

} // namespace epaperapi

#include "../external/waveshare/EPD_Common.h"