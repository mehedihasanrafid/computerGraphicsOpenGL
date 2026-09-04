#include "scenes/CityScene.hpp"

#include "GraphicsPrimitives.hpp"

#include <algorithm>
#include <array>
#include <cmath>

namespace yacht {
namespace {
using gfx::Color;

void drawBuilding(const float x, const float width, const float height, const Color color, const bool dayMode) {
    gfx::setColor(color);
    gfx::rectangle(x, -0.12F, width, height);
    gfx::setColor({0.03F, 0.04F, 0.07F});
    gfx::outlinedRectangle(x, -0.12F, width, height, 1.0F);

    const int columns = std::max(2, static_cast<int>(width / 0.08F));
    const int rows = std::max(2, static_cast<int>(height / 0.12F));
    const float gapX = width / static_cast<float>(columns + 1);
    const float gapY = height / static_cast<float>(rows + 1);
    const float windowW = std::min(0.045F, gapX * 0.55F);
    const float windowH = std::min(0.055F, gapY * 0.52F);

    for (int row = 1; row <= rows; ++row) {
        for (int col = 1; col <= columns; ++col) {
            const bool lit = ((row + col + static_cast<int>(x * 100.0F)) % 3) != 0;
            gfx::setColor(dayMode ? Color{0.50F, 0.78F, 0.92F} : (lit ? Color{1.0F, 0.76F, 0.18F} : Color{0.06F, 0.10F, 0.16F}));
            gfx::rectangle(x + gapX * static_cast<float>(col) - windowW * 0.5F, -0.12F + gapY * static_cast<float>(row) - windowH * 0.5F, windowW, windowH);
        }
    }
}

void drawTree(const float x, const float y, const float scale) {
    gfx::setColor({0.38F, 0.20F, 0.08F});
    gfx::rectangle(x - 0.012F * scale, y, 0.024F * scale, 0.14F * scale);
    gfx::setColor({0.04F, 0.43F, 0.16F});
    gfx::circle(x, y + 0.17F * scale, 0.09F * scale, 36);
    gfx::circle(x - 0.06F * scale, y + 0.14F * scale, 0.07F * scale, 32);
    gfx::circle(x + 0.06F * scale, y + 0.14F * scale, 0.07F * scale, 32);
}
}

void CityScene::draw(const AppState& state) const {
    gfx::verticalGradient(
        -1.6F, -0.9F, 1.6F, 0.9F,
        state.dayMode ? Color{0.72F, 0.88F, 0.98F} : Color{0.08F, 0.09F, 0.20F},
        state.dayMode ? Color{0.20F, 0.58F, 0.92F} : Color{0.01F, 0.02F, 0.09F}
    );

    gfx::setColor(state.dayMode ? Color{1.0F, 0.84F, 0.20F} : Color{0.92F, 0.95F, 1.0F});
    gfx::circle(-1.10F, 0.62F, 0.105F, 54);

    const float cloudShift = std::fmod(state.elapsedSeconds * 0.045F, 4.0F) - 2.0F;
    gfx::setColor(state.dayMode ? Color{1.0F, 1.0F, 1.0F, 0.90F} : Color{0.45F, 0.48F, 0.58F, 0.78F});
    gfx::cloud(cloudShift - 0.25F, 0.68F, 0.54F);
    gfx::cloud(cloudShift + 1.55F, 0.56F, 0.66F);

    const std::array<Color, 8> colors{{
        {0.75F, 0.20F, 0.18F}, {0.18F, 0.46F, 0.30F}, {0.20F, 0.32F, 0.65F}, {0.82F, 0.57F, 0.16F},
        {0.52F, 0.22F, 0.58F}, {0.28F, 0.31F, 0.35F}, {0.10F, 0.47F, 0.55F}, {0.68F, 0.34F, 0.20F}
    }};
    const std::array<float, 8> heights{{0.48F, 0.68F, 0.40F, 0.74F, 0.58F, 0.46F, 0.64F, 0.52F}};
    const float width = 0.35F;
    for (int i = 0; i < 8; ++i) {
        drawBuilding(-1.58F + static_cast<float>(i) * 0.40F, width, heights[static_cast<std::size_t>(i)], colors[static_cast<std::size_t>(i)], state.dayMode);
    }

    gfx::setColor({0.18F, 0.40F, 0.20F});
    gfx::rectangle(-1.6F, -0.20F, 3.2F, 0.12F);
    for (int i = 0; i < 12; ++i) {
        drawTree(-1.48F + static_cast<float>(i) * 0.28F, -0.20F, 0.65F);
    }

    gfx::verticalGradient(-1.6F, -0.9F, 1.6F, -0.22F, {0.0F, 0.16F, 0.32F}, {0.02F, 0.46F, 0.68F});
    gfx::setColor({0.70F, 0.88F, 0.98F, 0.45F});
    for (int i = 0; i < 7; ++i) {
        const float y = -0.32F - static_cast<float>(i) * 0.075F;
        gfx::line({-1.55F, y}, {1.55F, y}, 1.0F);
    }
}

bool CityScene::handleClick(const float worldX, const float worldY, AppState& state) const {
    const float dx = worldX + 1.10F;
    const float dy = worldY - 0.62F;
    if (dx * dx + dy * dy <= 0.14F * 0.14F) {
        state.dayMode = !state.dayMode;
        return true;
    }
    return false;
}

} // namespace yacht
