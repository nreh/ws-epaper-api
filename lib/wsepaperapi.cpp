#include "wsepaperapi.h"

#include <iostream>

using namespace std;

namespace epaperapi {
void Renderer::RegenerateBuffer() {
    // clear the old buffer values
    tempBuffer.FillBuffer(255); // fill with white color

    for (AbstractElement* elem : elements) {
        if (elem->visible) {
            elem->Draw(tempBuffer);
        }
    }
}
void Renderer::Refresh(RefreshMode mode, bool regenerateBuffer) {

    if (regenerateBuffer) {
        RegenerateBuffer();
    }

    drawTarget.Refresh(tempBuffer, mode);
}

} // namespace epaperapi