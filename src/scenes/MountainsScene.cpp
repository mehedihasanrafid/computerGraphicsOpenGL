#include "scenes/MountainsScene.hpp"

#include "GraphicsPrimitives.hpp"

#include <cmath>

namespace yacht {
namespace {
using gfx::Color;

void drawPine(const float x, const float y, const float scale) {
    gfx::setColor({0.28F, 0.16F, 0.07F});
    gfx::rectangle(x - 0.015F * scale, y, 0.03F * scale, 0.22F * scale);
    gfx::setColor({0.03F, 0.30F, 0.12F});
    gfx::triangle({x, y + 0.46F * scale}, {x - 0.16F * scale, y + 0.14F * scale}, {x + 0.16F * scale, y + 0.14F * scale});
    gfx::triangle({x, y + 0.36F * scale}, {x - 0.14F * scale, y + 0.05F * scale}, {x + 0.14F * scale, y + 0.05F * scale});
}
}

void MountainsScene::draw(const AppState& state) const {
    gfx::verticalGradient(
        -1.6F, -0.9F, 1.6F, 0.9F,
        state.dayMode ? Color{0.72F, 0.86F, 0.96F} : Color{0.10F, 0.10F, 0.22F},
        state.dayMode ? Color{0.22F, 0.52F, 0.84F} : Color{0.01F, 0.02F, 0.10F}
    );

    gfx::setColor(state.dayMode ? Color{1.0F, 0.88F, 0.22F} : Color{0.94F, 0.96F, 1.0F});
    gfx::circle(0.92F, 0.60F, 0.11F, 54);

    const float drift = std::fmod(state.elapsedSeconds * 0.05F, 3.7F) - 1.9F;
    gfx::setColor(state.dayMode ? Color{1.0F, 1.0F, 1.0F, 0.9F} : Color{0.48F, 0.52F, 0.62F, 0.8F});
    gfx::cloud(drift - 0.45F, 0.60F, 0.62F);
    gfx::cloud(drift + 1.15F, 0.72F, 0.50F);

    gfx::setColor({0.15F, 0.28F, 0.23F});
    gfx::triangle({-1.7F, -0.12F}, {-1.15F, 0.58F}, {-0.52F, -0.12F});
    gfx::triangle({-0.90F, -0.12F}, {-0.22F, 0.72F}, {0.48F, -0.12F});
    gfx::triangle({-0.05F, -0.12F}, {0.62F, 0.50F}, {1.25F, -0.12F});
    gfx::triangle({0.70F, -0.12F}, {1.32F, 0.42F}, {1.72F, -0.12F});

    gfx::setColor({0.90F, 0.94F, 0.95F});
    gfx::triangle({-1.37F, 0.30F}, {-1.15F, 0.58F}, {-0.90F, 0.29F});
    gfx::triangle({-0.48F, 0.40F}, {-0.22F, 0.72F}, {0.05F, 0.39F});
    gfx::triangle({0.40F, 0.28F}, {0.62F, 0.50F}, {0.85F, 0.28F});

    gfx::setColor({0.11F, 0.42F, 0.18F});
    gfx::polygon({{-1.6F, -0.25F}, {-1.6F, -0.05F}, {-0.85F, 0.02F}, {-0.20F, -0.08F}, {0.62F, 0.01F}, {1.6F, -0.07F}, {1.6F, -0.25F}});

    gfx::verticalGradient(-1.6F, -0.9F, 1.6F, -0.20F, {0.0F, 0.16F, 0.34F}, {0.03F, 0.46F, 0.68F});

    drawPine(-1.30F, -0.25F, 0.70F);
    drawPine(-1.02F, -0.23F, 0.58F);
    drawPine(1.18F, -0.23F, 0.68F);
    drawPine(1.42F, -0.22F, 0.52F);

    const float planeX = std::fmod(state.elapsedSeconds * 0.18F, 3.8F) - 1.9F;
    gfx::setColor({0.92F, 0.92F, 0.95F});
    gfx::polygon({{planeX - 0.12F, 0.38F}, {planeX + 0.12F, 0.38F}, {planeX + 0.18F, 0.41F}, {planeX + 0.12F, 0.44F}, {planeX - 0.12F, 0.44F}});
    gfx::setColor({0.14F, 0.34F, 0.70F});
    gfx::triangle({planeX - 0.02F, 0.41F}, {planeX - 0.14F, 0.52F}, {planeX + 0.04F, 0.42F});
    gfx::triangle({planeX - 0.02F, 0.41F}, {planeX - 0.12F, 0.31F}, {planeX + 0.06F, 0.40F});
}

bool MountainsScene::handleClick(const float worldX, const float worldY, AppState& state) const {
    const float dx = worldX - 0.92F;
    const float dy = worldY - 0.60F;
    if (dx * dx + dy * dy <= 0.14F * 0.14F) {
        state.dayMode = !state.dayMode;
        return true;
    }
    return false;
}

} // namespace yacht
