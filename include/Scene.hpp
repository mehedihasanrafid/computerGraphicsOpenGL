#pragma once

#include "AppState.hpp"

namespace yacht {

class Scene {
public:
    virtual ~Scene() = default;
    virtual void draw(const AppState& state) const = 0;
    virtual bool handleClick(float worldX, float worldY, AppState& state) const;
};

} // namespace yacht
