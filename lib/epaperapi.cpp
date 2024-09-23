#include "epaperapi.h"

#include <iostream>

using namespace std;

namespace epaperapi {
void Renderer::RegenerateBuffer() {
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

    switch (mode) {

    case RefreshMode::Normal:
        drawTarget.Refresh(tempBuffer);
        break;

    case RefreshMode::Fast:
        drawTarget.RefreshFast(tempBuffer);
        break;

    case RefreshMode::Partial:
        drawTarget.PartialRefresh(tempBuffer);
        break;

    default:
        return;
    }
}

} // namespace epaperapi