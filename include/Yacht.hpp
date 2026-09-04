#pragma once

#include "AppState.hpp"

namespace yacht {

class Yacht {
public:
    // Draws the original university-project yacht design without replacing
    // its hull, decks, cabin, antenna, windows, or Bangladesh flag geometry.
    void draw(const AppState& state) const;
};

} // namespace yacht
