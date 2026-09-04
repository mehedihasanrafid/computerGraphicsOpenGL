#include "Audio.hpp"

#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#endif

namespace yacht::audio {

void notifySceneChange(const bool enabled) {
    if (!enabled) {
        return;
    }
#if defined(_WIN32)
    MessageBeep(MB_OK);
#endif
}

} // namespace yacht::audio
