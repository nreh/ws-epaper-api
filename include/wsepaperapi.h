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

enum class RefreshMode { Normal, Fast, Partial };

/// @brief Abstract class representing something that can be drawn on. Usually an E-Paper display.
class AbstractDrawTarget {
  public:
    /// @brief Initializes the display and runs logic - if any - that might be necessary before the display can be used.
    virtual void Init() = 0;

    uint16_t width, height;

    /// @brief Contains pixels that are currently being displayed. Useful for partial refreshes where we need the old pixel
    /// values.
    AbstractBuffer& buffer;

    /// @brief Refresh the display, showing the contents of the buffer.
    virtual void Refresh(RefreshMode mode) = 0;

    /// @brief Clear the display to white
    virtual void Clear() = 0;

    /// @brief Enter sleep mode
    virtual void Sleep() = 0;

    AbstractDrawTarget(AbstractBuffer& _buffer) : buffer(_buffer) {}
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
        SetTransformation(transformation);
    }

    /// @brief Go through all visible Elements and draw them onto the buffer.
    void RegenerateBuffer();

    /// @brief Draw all visible elements onto the draw target
    /// @param mode How the display should be refreshed
    /// @param regenerateBuffer If true, all visible elements have their Draw() function called and the buffer is
    /// regenerated. You can disble this if you know no changes have been made to the elements.
    void Refresh(RefreshMode mode = RefreshMode::Normal, bool regenerateBuffer = true);

    /// @brief Change what transformation is performed on the buffer before being set to the DrawTarget. Useful if your
    /// display is physically rotated and you want your coordinate system to reflect that.
    /// @param _transformation
    void SetTransformation(BufferTransform _transformation);

    ~Renderer();
};

} // namespace epaperapi