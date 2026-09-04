#pragma once

#include "Scene.hpp"

namespace yacht {

class HarborScene final : public Scene {
public:
    void draw(const AppState& state) const override;
    bool handleClick(float worldX, float worldY, AppState& state) const override;
};

} // namespace yacht
