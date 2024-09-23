#pragma once

#include "buffers.h"
#include "elements.h"

#include <stdint.h>
#include <vector>

namespace epaperapi {

/// @brief Abstract class representing something that can be drawn on. Usually a e-Paper display.
class AbstractDrawTarget {
  private:
    virtual void Init() = 0;

  public:
    uint16_t width, height;

    /// @brief Contains pixels that have yet to be drawn
    AbstractBuffer& tempBuffer;
    /// @brief Contains pixels that are currently being displayed
    AbstractBuffer& buffer;

    /// @brief Refresh the display
    virtual void Refresh(AbstractBuffer& _buffer) = 0;
    virtual void RefreshFast(AbstractBuffer& _buffer) = 0;
    /// @brief Partially refresh the display
    virtual void PartialRefresh(AbstractBuffer& _buffer) = 0;
    /// @brief Clear the display to white
    virtual void Clear() = 0;
    /// @brief Clear the display to black
    virtual void ClearBlack() = 0;
    /// @brief Enter sleep mode
    virtual void Sleep() = 0;

    AbstractDrawTarget(AbstractBuffer& _buffer, AbstractBuffer& _tempbuffer) : buffer(_buffer), tempBuffer(_tempbuffer) {}
};

/// @brief Something that draws Elements to a drawing target
class Renderer {
  private:
    /// @brief Our elements are drawn onto this buffer before being sent to the draw target
    AbstractBuffer& tempBuffer;

  public:
    enum RefreshMode { Normal, Fast, Partial };

    /// @brief List of Elements that are to be drawn
    std::vector<AbstractElement*> elements;

    /// @brief What to draw on
    AbstractDrawTarget& drawTarget;

    Renderer(AbstractDrawTarget& _drawTarget) : drawTarget(_drawTarget), tempBuffer(_drawTarget.tempBuffer) {}

    /// @brief Go through all visible Elements and draw them onto the buffer.
    void RegenerateBuffer();

    /// @brief Draw all visible elements onto the draw target
    void Refresh(RefreshMode mode = RefreshMode::Normal, bool regenerateBuffer = true);
};

} // namespace epaperapi