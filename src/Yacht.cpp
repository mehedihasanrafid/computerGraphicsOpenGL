#include "Yacht.hpp"

#include "GraphicsPrimitives.hpp"

#if defined(_WIN32)
#include <windows.h>
#endif
#include <GL/glut.h>

#include <cmath>

namespace yacht {
namespace {

constexpr float PI = 3.14159265358979323846f;

void drawRectangle(float centerX, float centerY, float width, float height) {
    const float halfWidth = width / 2.0f;
    const float halfHeight = height / 2.0f;

    glBegin(GL_QUADS);
    glVertex2f(centerX - halfWidth, centerY - halfHeight);
    glVertex2f(centerX + halfWidth, centerY - halfHeight);
    glVertex2f(centerX + halfWidth, centerY + halfHeight);
    glVertex2f(centerX - halfWidth, centerY + halfHeight);
    glEnd();
}

void drawCircle(float centerX, float centerY, float radius) {
    constexpr int segments = 100;
    const float angleStep = 2.0f * PI / static_cast<float>(segments);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);

    for (int i = 0; i <= segments; ++i) {
        const float angle = static_cast<float>(i) * angleStep;
        glVertex2f(
            centerX + radius * std::cos(angle),
            centerY + radius * std::sin(angle)
        );
    }

    glEnd();
}

void drawCircleWithoutFill(float centerX, float centerY, float radius) {
    constexpr int segments = 100;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        const float angle =
            2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);

        glVertex2f(
            centerX + radius * std::cos(angle),
            centerY + radius * std::sin(angle)
        );
    }
    glEnd();
}

void drawOriginalFlag(const float flagWaveX, const float flagWaveY) {
    float bezierX[200];
    float bezierTop[200];
    float bezierBottom[200];

    const float controlX[4] = {
        0.625f - flagWaveX,
        0.675f,
        0.675f,
        0.75f
    };

    const float controlTop[4] = {
        0.325f,
        0.325f + flagWaveY,
        0.325f - flagWaveY,
        0.325f
    };

    const float controlBottom[4] = {
        0.2f,
        0.2f + flagWaveY,
        0.2f - flagWaveY,
        0.2f
    };

    float t = 0.0f;
    for (int i = 0; i < 200; ++i, t += 0.005f) {
        const float u = 1.0f - t;

        bezierX[i] =
            u * u * u * controlX[0] +
            3.0f * u * u * t * controlX[1] +
            3.0f * u * t * t * controlX[2] +
            t * t * t * controlX[3];

        bezierTop[i] =
            u * u * u * controlTop[0] +
            3.0f * u * u * t * controlTop[1] +
            3.0f * u * t * t * controlTop[2] +
            t * t * t * controlTop[3];

        bezierBottom[i] =
            u * u * u * controlBottom[0] +
            3.0f * u * u * t * controlBottom[1] +
            3.0f * u * t * t * controlBottom[2] +
            t * t * t * controlBottom[3];
    }

    // Green field of the Bangladesh flag.
    glColor3f(0.122f, 0.388f, 0.063f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < 200; ++i) {
        glVertex2f(bezierX[i], bezierTop[i]);
        glVertex2f(bezierX[i], bezierBottom[i]);
    }
    glEnd();

    // Red disc.
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(
        bezierX[110],
        (bezierTop[110] + bezierBottom[110]) / 2.0f,
        0.035f
    );

    // Flag pole.
    glColor3f(0.792f, 0.839f, 0.851f);
    drawRectangle(0.75f, 0.2f, 0.008f, 0.28f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawRectangle(0.75f, 0.2f, 0.008f, 0.28f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawDeck() {
    // Main hull.
    glColor3f(0.1f, 0.1f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, -0.25f);
    glVertex2f(0.5f, -0.25f);
    glVertex2f(0.65f, -0.1f);
    glVertex2f(-0.8f, -0.1f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, -0.25f);
    glVertex2f(0.5f, -0.25f);
    glVertex2f(0.65f, -0.1f);
    glVertex2f(-0.8f, -0.1f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Ship first floor.
    glColor3f(0.6f, 0.0f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.45f, -0.1f);
    glVertex2f(0.65f, -0.1f);
    glVertex2f(0.45f, 0.125f);
    glVertex2f(-0.35f, 0.125f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.45f, -0.1f);
    glVertex2f(0.65f, -0.1f);
    glVertex2f(0.45f, 0.125f);
    glVertex2f(-0.35f, 0.125f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // First-floor black window strip.
    glColor3f(0.0f, 0.0f, 0.0f);
    drawRectangle(0.1f, 0.058f, 0.7f, 0.09f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(0.1f, 0.058f, 0.7f, 0.09f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(0.1f, 0.06f, 0.01f, 0.08f);
    drawRectangle(0.15f, 0.06f, 0.01f, 0.08f);
    drawRectangle(-0.2f, 0.06f, 0.01f, 0.08f);
    drawRectangle(0.2f, 0.06f, 0.01f, 0.08f);

    // Metallic upper deck.
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.65f, -0.1f);
    glVertex2f(0.65f, -0.1f);
    glVertex2f(0.85f, 0.065f);
    glVertex2f(0.3f, 0.065f);
    glVertex2f(0.25f, 0.02f);
    glVertex2f(-0.65f, 0.02f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.65f, -0.1f);
    glVertex2f(0.65f, -0.1f);
    glVertex2f(0.85f, 0.065f);
    glVertex2f(0.3f, 0.065f);
    glVertex2f(0.25f, 0.02f);
    glVertex2f(-0.65f, 0.02f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Front deck.
    glColor3f(0.1f, 0.6f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.65f, -0.1f);
    glVertex2f(0.65f, -0.1f);
    glVertex2f(0.8f, 0.02f);
    glVertex2f(0.3f, 0.02f);
    glVertex2f(0.25f, -0.025f);
    glVertex2f(-0.65f, -0.025f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.65f, -0.1f);
    glVertex2f(0.65f, -0.1f);
    glVertex2f(0.8f, 0.02f);
    glVertex2f(0.3f, 0.02f);
    glVertex2f(0.25f, -0.025f);
    glVertex2f(-0.65f, -0.025f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Circular deck windows.
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.4f, -0.06f, 0.025f);
    drawCircle(-0.3f, -0.06f, 0.025f);
    drawCircle(-0.5f, -0.06f, 0.025f);
    drawCircle(-0.2f, -0.06f, 0.025f);
    drawCircle(0.3f, -0.06f, 0.025f);
    drawCircle(0.5f, -0.06f, 0.025f);

    glLineWidth(3.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircleWithoutFill(0.5f, -0.06f, 0.025f);
    drawCircleWithoutFill(0.3f, -0.06f, 0.025f);
    drawCircleWithoutFill(-0.2f, -0.06f, 0.025f);
    drawCircleWithoutFill(-0.5f, -0.06f, 0.025f);
    drawCircleWithoutFill(-0.3f, -0.06f, 0.025f);
    drawCircleWithoutFill(-0.4f, -0.06f, 0.025f);

    // Center decoration.
    glColor3f(0.208f, 0.718f, 0.878f);
    drawRectangle(0.04f, -0.06f, 0.3f, 0.025f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(0.04f, -0.06f, 0.3f, 0.025f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawSail() {
    // Sail-deck platform.
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.55f, 0.125f);
    glVertex2f(0.35f, 0.125f);
    glVertex2f(0.3f, 0.15f);
    glVertex2f(-0.5f, 0.15f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.55f, 0.125f);
    glVertex2f(0.35f, 0.125f);
    glVertex2f(0.3f, 0.15f);
    glVertex2f(-0.5f, 0.15f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Second floor.
    glColor3f(0.9f, 0.8f, 0.95f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.225f);
    glVertex2f(-0.4f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(-0.2f, 0.15f);
    glVertex2f(0.3f, 0.15f);
    glVertex2f(0.2f, 0.225f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.225f);
    glVertex2f(-0.4f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(-0.2f, 0.15f);
    glVertex2f(0.3f, 0.15f);
    glVertex2f(0.2f, 0.225f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Second-floor windows.
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.1f, 0.215f);
    glVertex2f(0.21f, 0.215f);
    glVertex2f(0.29f, 0.16f);
    glVertex2f(0.1f, 0.16f);
    glEnd();

    drawCircle(0.1f, 0.1875f, 0.0275f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawRectangle(-0.08f, 0.1875f, 0.225f, 0.05f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(-0.08f, 0.1875f, 0.225f, 0.05f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Third floor.
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.225f);
    glVertex2f(0.2f, 0.225f);
    glVertex2f(0.12f, 0.3f);
    glVertex2f(0.0f, 0.3f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.225f);
    glVertex2f(0.2f, 0.225f);
    glVertex2f(0.12f, 0.3f);
    glVertex2f(0.0f, 0.3f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Third-floor windows.
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.05f, 0.235f);
    glVertex2f(0.19f, 0.235f);
    glVertex2f(0.13f, 0.29f);
    glVertex2f(0.05f, 0.29f);
    glEnd();

    drawCircle(0.05f, 0.2625f, 0.0275f);

    // Rudder/control tower.
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.225f);
    glVertex2f(-0.15f, 0.225f);
    glVertex2f(-0.2f, 0.35f);
    glVertex2f(-0.25f, 0.35f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.225f);
    glVertex2f(-0.15f, 0.225f);
    glVertex2f(-0.2f, 0.35f);
    glVertex2f(-0.25f, 0.35f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Rudder decorations.
    glColor3f(0.0f, 0.0f, 1.0f);
    drawRectangle(-0.215f, 0.3f, 0.07f, 0.01f);
    drawRectangle(-0.22f, 0.325f, 0.06f, 0.01f);

    // Fence/rail.
    glColor3f(0.412f, 0.549f, 0.722f);
    drawRectangle(-0.3f, 0.175f, 0.4f, 0.007f);
    drawRectangle(-0.5f, 0.165f, 0.007f, 0.03f);
    drawRectangle(-0.45f, 0.165f, 0.007f, 0.03f);
    drawRectangle(-0.4f, 0.165f, 0.007f, 0.03f);
    drawRectangle(-0.35f, 0.165f, 0.007f, 0.03f);
    drawRectangle(-0.3f, 0.165f, 0.007f, 0.03f);
    drawRectangle(-0.25f, 0.165f, 0.007f, 0.03f);
    drawRectangle(-0.2f, 0.165f, 0.007f, 0.03f);
    drawRectangle(-0.15f, 0.165f, 0.007f, 0.03f);
    drawRectangle(-0.1f, 0.165f, 0.007f, 0.03f);

    // Antenna platform.
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0.02f, 0.3f);
    glVertex2f(0.085f, 0.3f);
    glVertex2f(0.0625f, 0.35f);
    glVertex2f(0.03f, 0.35f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.02f, 0.3f);
    glVertex2f(0.085f, 0.3f);
    glVertex2f(0.0625f, 0.35f);
    glVertex2f(0.03f, 0.35f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Antenna.
    glColor3f(0.412f, 0.549f, 0.722f);
    drawRectangle(0.04625f, 0.425f, 0.008f, 0.15f);
    drawRectangle(0.04625f, 0.435f, 0.06f, 0.008f);
    drawRectangle(0.04625f, 0.455f, 0.07f, 0.008f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawRectangle(0.04625f, 0.425f, 0.008f, 0.15f);
    drawRectangle(0.04625f, 0.435f, 0.06f, 0.008f);
    drawRectangle(0.04625f, 0.455f, 0.07f, 0.008f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void drawWake(const AppState& state) {
    if (state.paused) {
        return;
    }

    glPushMatrix();
    glTranslatef(state.yachtX - 0.52F, state.yachtY - 0.18F, 0.0F);
    gfx::setColor({0.85F, 0.95F, 1.0F, 0.65F});
    for (int i = 0; i < 4; ++i) {
        const float phase = std::fmod(
            state.elapsedSeconds * 0.7F + static_cast<float>(i) * 0.22F,
            1.0F
        );
        const float width = 0.16F + phase * 0.22F;
        gfx::ellipse(-phase * 0.22F, 0.0F, width, 0.018F, 28);
    }
    glPopMatrix();
}

} // namespace

void Yacht::draw(const AppState& state) const {
    drawWake(state);

    const float waveY = state.flagAnimating
        ? std::sin(state.elapsedSeconds * 5.5F) * 0.05F
        : 0.0F;
    const float waveX = state.flagAnimating
        ? std::sin(state.elapsedSeconds * 3.8F) * 0.01F
        : 0.0F;

    glPushMatrix();
    glTranslatef(state.yachtX, state.yachtY, 0.0F);
    glScalef(0.72F, 0.72F, 1.0F);

    drawDeck();
    drawSail();
    drawOriginalFlag(waveX, waveY);

    glPopMatrix();
}

} // namespace yacht
