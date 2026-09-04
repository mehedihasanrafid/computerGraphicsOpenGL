#include "scenes/BeachScene.hpp"

#include "GraphicsPrimitives.hpp"

#if defined(_WIN32)
#include <windows.h>
#endif
#include <GL/glut.h>

#include <cmath>

namespace yacht {
namespace {
using gfx::Color;
using gfx::Vec2;

void drawPalm(const float x, const float y, const float scale) {
    gfx::setColor({0.42F, 0.24F, 0.10F});
    gfx::polygon({
        {x - 0.025F * scale, y},
        {x + 0.025F * scale, y},
        {x + 0.008F * scale, y + 0.43F * scale},
        {x - 0.015F * scale, y + 0.43F * scale}
    });

    gfx::setColor({0.05F, 0.48F, 0.14F});
    const Vec2 crown{x, y + 0.43F * scale};
    gfx::polygon({crown, {x - 0.24F * scale, y + 0.50F * scale}, {x - 0.08F * scale, y + 0.39F * scale}});
    gfx::polygon({crown, {x + 0.24F * scale, y + 0.50F * scale}, {x + 0.08F * scale, y + 0.39F * scale}});
    gfx::polygon({crown, {x - 0.18F * scale, y + 0.65F * scale}, {x - 0.02F * scale, y + 0.45F * scale}});
    gfx::polygon({crown, {x + 0.18F * scale, y + 0.65F * scale}, {x + 0.02F * scale, y + 0.45F * scale}});
    gfx::polygon({crown, {x, y + 0.70F * scale}, {x + 0.05F * scale, y + 0.46F * scale}});
}

void drawUmbrella(const float x, const float y, const float scale) {
    gfx::setColor({0.38F, 0.20F, 0.10F});
    gfx::rectangle(x - 0.008F * scale, y, 0.016F * scale, 0.26F * scale);
    gfx::setColor({0.82F, 0.13F, 0.22F});
    gfx::polygon({
        {x - 0.25F * scale, y + 0.25F * scale},
        {x, y + 0.42F * scale},
        {x + 0.25F * scale, y + 0.25F * scale}
    });
    gfx::setColor({0.98F, 0.82F, 0.18F});
    gfx::triangle({x - 0.08F * scale, y + 0.25F * scale}, {x, y + 0.42F * scale}, {x + 0.08F * scale, y + 0.25F * scale});
}
}

void BeachScene::draw(const AppState& state) const {
    const Color top = state.dayMode ? Color{0.20F, 0.60F, 0.95F} : Color{0.02F, 0.03F, 0.16F};
    const Color bottom = state.dayMode ? Color{0.98F, 0.56F, 0.32F} : Color{0.18F, 0.08F, 0.28F};
    gfx::verticalGradient(-1.6F, -0.9F, 1.6F, 0.9F, bottom, top);

    gfx::setColor(state.dayMode ? Color{1.0F, 0.80F, 0.18F} : Color{0.92F, 0.94F, 1.0F});
    gfx::circle(1.05F, 0.58F, 0.12F, 56);
    if (!state.dayMode) {
        gfx::setColor({0.08F, 0.05F, 0.18F});
        gfx::circle(1.10F, 0.62F, 0.105F, 56);
        gfx::setColor({1.0F, 1.0F, 1.0F});
        for (int i = 0; i < 16; ++i) {
            const float x = -1.45F + static_cast<float>((i * 37) % 90) / 30.0F;
            const float y = 0.18F + static_cast<float>((i * 19) % 60) / 90.0F;
            gfx::star(x, y, 0.012F, 0.005F, 5);
        }
    }

    const float cloudShift = std::fmod(state.elapsedSeconds * 0.06F, 3.8F) - 1.9F;
    gfx::setColor(state.dayMode ? Color{1.0F, 1.0F, 1.0F, 0.92F} : Color{0.55F, 0.58F, 0.70F, 0.78F});
    gfx::cloud(cloudShift - 0.65F, 0.55F, 0.75F);
    gfx::cloud(cloudShift + 1.25F, 0.70F, 0.55F);

    gfx::setColor({0.22F, 0.28F, 0.26F});
    gfx::triangle({-1.6F, -0.05F}, {-1.05F, 0.52F}, {-0.48F, -0.05F});
    gfx::triangle({-0.85F, -0.05F}, {-0.20F, 0.43F}, {0.52F, -0.05F});
    gfx::setColor({0.86F, 0.90F, 0.92F});
    gfx::triangle({-1.30F, 0.26F}, {-1.05F, 0.52F}, {-0.82F, 0.27F});
    gfx::triangle({-0.40F, 0.28F}, {-0.20F, 0.43F}, {-0.03F, 0.28F});

    gfx::verticalGradient(-1.6F, -0.55F, 1.6F, 0.12F, {0.0F, 0.20F, 0.42F}, {0.05F, 0.60F, 0.82F});

    gfx::setColor({0.86F, 0.72F, 0.42F});
    gfx::polygon({{-1.6F, -0.9F}, {1.6F, -0.9F}, {1.6F, -0.58F}, {-0.55F, -0.48F}, {-1.6F, -0.58F}});

    gfx::setColor({0.95F, 0.96F, 1.0F, 0.75F});
    for (int i = 0; i < 8; ++i) {
        const float x = -1.55F + static_cast<float>(i) * 0.44F;
        gfx::ellipse(x, -0.50F + 0.02F * std::sin(state.elapsedSeconds * 2.0F + static_cast<float>(i)), 0.14F, 0.015F, 30);
    }

    drawPalm(-1.25F, -0.88F, 0.9F);
    drawPalm(1.32F, -0.90F, 0.78F);
    drawUmbrella(0.78F, -0.86F, 0.72F);
}

bool BeachScene::handleClick(const float worldX, const float worldY, AppState& state) const {
    const float dx = worldX - 1.05F;
    const float dy = worldY - 0.58F;
    if (dx * dx + dy * dy <= 0.15F * 0.15F) {
        state.dayMode = !state.dayMode;
        return true;
    }
    return false;
}

} // namespace yacht
