#include "scenes/HarborScene.hpp"

#include "GraphicsPrimitives.hpp"

#include <array>
#include <cmath>

namespace yacht {
namespace {
using gfx::Color;

void drawContainer(const float x, const float y, const float width, const float height, const Color color) {
    gfx::setColor(color);
    gfx::rectangle(x, y, width, height);
    gfx::setColor({0.07F, 0.07F, 0.08F});
    gfx::outlinedRectangle(x, y, width, height, 1.0F);
    for (int i = 1; i < 6; ++i) {
        const float sx = x + width * static_cast<float>(i) / 6.0F;
        gfx::line({sx, y}, {sx, y + height}, 0.6F);
    }
}

void drawCrane(const float x, const float y, const float scale) {
    gfx::setColor({0.95F, 0.58F, 0.08F});
    gfx::rectangle(x, y, 0.05F * scale, 0.65F * scale);
    gfx::rectangle(x, y + 0.60F * scale, 0.50F * scale, 0.045F * scale);
    gfx::line({x + 0.45F * scale, y + 0.60F * scale}, {x + 0.45F * scale, y + 0.24F * scale}, 2.0F);
    gfx::setColor({0.10F, 0.10F, 0.11F});
    gfx::line({x + 0.025F * scale, y}, {x + 0.40F * scale, y + 0.60F * scale}, 2.0F);
}

void drawCargoShip(const float x, const float y, const float scale) {
    gfx::setColor({0.10F, 0.16F, 0.26F});
    gfx::polygon({
        {x - 0.52F * scale, y},
        {x + 0.52F * scale, y},
        {x + 0.44F * scale, y - 0.13F * scale},
        {x - 0.42F * scale, y - 0.13F * scale}
    });
    gfx::setColor({0.78F, 0.10F, 0.10F});
    gfx::rectangle(x - 0.42F * scale, y - 0.16F * scale, 0.84F * scale, 0.04F * scale);

    const std::array<Color, 5> colors{{
        {0.75F, 0.16F, 0.15F}, {0.08F, 0.36F, 0.70F}, {0.12F, 0.55F, 0.24F}, {0.86F, 0.55F, 0.10F}, {0.45F, 0.18F, 0.58F}
    }};
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 4; ++col) {
            drawContainer(
                x - 0.38F * scale + static_cast<float>(col) * 0.18F * scale,
                y + 0.02F * scale + static_cast<float>(row) * 0.09F * scale,
                0.17F * scale,
                0.08F * scale,
                colors[static_cast<std::size_t>((row * 4 + col) % colors.size())]
            );
        }
    }

    gfx::setColor({0.92F, 0.94F, 0.95F});
    gfx::rectangle(x + 0.30F * scale, y + 0.02F * scale, 0.15F * scale, 0.28F * scale);
    gfx::setColor({0.06F, 0.13F, 0.22F});
    gfx::rectangle(x + 0.33F * scale, y + 0.20F * scale, 0.09F * scale, 0.05F * scale);
}

void drawSmallBoat(const float x, const float y, const float scale) {
    gfx::setColor({0.20F, 0.22F, 0.24F});
    gfx::polygon({{x - 0.15F * scale, y}, {x + 0.15F * scale, y}, {x + 0.11F * scale, y - 0.06F * scale}, {x - 0.10F * scale, y - 0.06F * scale}});
    gfx::setColor({0.90F, 0.90F, 0.88F});
    gfx::rectangle(x - 0.04F * scale, y, 0.10F * scale, 0.08F * scale);
}
}

void HarborScene::draw(const AppState& state) const {
    gfx::verticalGradient(
        -1.6F, -0.9F, 1.6F, 0.9F,
        state.dayMode ? Color{0.74F, 0.87F, 0.95F} : Color{0.10F, 0.11F, 0.21F},
        state.dayMode ? Color{0.24F, 0.58F, 0.86F} : Color{0.02F, 0.03F, 0.10F}
    );

    gfx::setColor(state.dayMode ? Color{1.0F, 0.84F, 0.18F} : Color{0.93F, 0.95F, 1.0F});
    gfx::circle(-0.95F, 0.64F, 0.105F, 54);

    const float shift = std::fmod(state.elapsedSeconds * 0.055F, 3.9F) - 1.95F;
    gfx::setColor(state.dayMode ? Color{1.0F, 1.0F, 1.0F, 0.90F} : Color{0.48F, 0.50F, 0.59F, 0.80F});
    gfx::cloud(shift - 0.45F, 0.64F, 0.58F);
    gfx::cloud(shift + 1.35F, 0.73F, 0.48F);

    gfx::setColor({0.27F, 0.24F, 0.19F});
    gfx::rectangle(-1.6F, -0.05F, 3.2F, 0.22F);
    gfx::setColor({0.15F, 0.14F, 0.13F});
    gfx::rectangle(-1.6F, -0.09F, 3.2F, 0.04F);

    const std::array<Color, 6> colors{{
        {0.82F, 0.17F, 0.14F}, {0.07F, 0.35F, 0.70F}, {0.12F, 0.55F, 0.24F},
        {0.90F, 0.62F, 0.08F}, {0.46F, 0.18F, 0.60F}, {0.52F, 0.30F, 0.16F}
    }};
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 7 - row; ++col) {
            drawContainer(-1.42F + static_cast<float>(col) * 0.30F + static_cast<float>(row) * 0.15F, 0.18F + static_cast<float>(row) * 0.12F, 0.28F, 0.105F, colors[static_cast<std::size_t>((row + col) % colors.size())]);
        }
    }

    drawCrane(0.75F, 0.16F, 0.90F);
    drawCrane(1.18F, 0.16F, 0.70F);

    gfx::verticalGradient(-1.6F, -0.9F, 1.6F, -0.10F, {0.0F, 0.13F, 0.29F}, {0.02F, 0.42F, 0.62F});

    drawCargoShip(-0.25F, -0.28F, 0.78F);
    const float boatX = std::fmod(state.elapsedSeconds * 0.16F, 3.8F) - 1.9F;
    drawSmallBoat(boatX, -0.66F, 0.75F);
    drawSmallBoat(-boatX * 0.65F, -0.78F, 0.55F);
}

bool HarborScene::handleClick(const float worldX, const float worldY, AppState& state) const {
    const float dx = worldX + 0.95F;
    const float dy = worldY - 0.64F;
    if (dx * dx + dy * dy <= 0.14F * 0.14F) {
        state.dayMode = !state.dayMode;
        return true;
    }
    return false;
}

} // namespace yacht
