#pragma once

#include "buffers.h"
#include "bufferutils.h"
#include "elements.h"

#include <stdint.h>
#include <vector>

namespace epaperapi {

/// @brief Abstract class representing something that can be drawn on. Usually an E-Paper display.
class AbstractDrawTarget {
  public:
    /// @brief Initializes the display and runs logic - if any - that might be necessary before the display can be used.
    virtual void Init() = 0;

    uint16_t width, height;

    /// @brief Contains pixels that have yet to be drawn
    AbstractBuffer& tempBuffer;
    /// @brief Contains pixels that are currently being displayed. Useful for partial refreshes where we need the old pixel
    /// values.
    AbstractBuffer& buffer;

    /// @brief Refresh the display, showing the contents of the buffer.
    virtual void Refresh(AbstractBuffer& _buffer) = 0;

    /// @brief Clear the display to white
    virtual void Clear() = 0;

    /// @brief Enter sleep mode
    virtual void Sleep() = 0;

    AbstractDrawTarget(AbstractBuffer& _buffer, AbstractBuffer& _tempbuffer) : buffer(_buffer), tempBuffer(_tempbuffer) {}
};

/// @brief Handles draw calls to the draw target as well as holding a list of all elements to be drawn.
class Renderer {
  private:
    /// @brief Our elements are drawn onto this buffer before being sent to the draw target.
    AbstractBuffer& tempBuffer;

  public:
    enum RefreshMode { Normal, Fast, Partial };

    /// @brief List of Elements that are to be drawn
    std::vector<AbstractElement*> elements;

    /// @brief Draw target that visible elements will be drawn on
    AbstractDrawTarget& drawTarget;

    Renderer(AbstractDrawTarget& _drawTarget) : drawTarget(_drawTarget), tempBuffer(_drawTarget.tempBuffer) {}

    /// @brief Go through all visible Elements and draw them onto the buffer.
    void RegenerateBuffer();

    /// @brief Draw all visible elements onto the draw target
    /// @param mode How the display should be refreshed
    /// @param regenerateBuffer If true, all visible elements have their Draw() function called and the buffer is
    /// regenerated. You can disble this if you know no changes have been made to the elements.
    void Refresh(RefreshMode mode = RefreshMode::Normal, bool regenerateBuffer = true);
};

} // namespace epaperapi