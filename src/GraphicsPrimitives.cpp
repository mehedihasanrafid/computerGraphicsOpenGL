#include "GraphicsPrimitives.hpp"

#if defined(_WIN32)
#include <windows.h>
#endif
#include <GL/glut.h>

#include <algorithm>
#include <cmath>

namespace yacht::gfx {
namespace {
constexpr float kPi = 3.14159265358979323846F;
void* defaultFont() { return GLUT_BITMAP_8_BY_13; }
}

void setColor(const Color color) {
    glColor4f(color.r, color.g, color.b, color.a);
}

void rectangle(const float x, const float y, const float width, const float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void outlinedRectangle(const float x, const float y, const float width, const float height, const float lineWidth) {
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void circle(const float cx, const float cy, const float radius, const int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        const float angle = 2.0F * kPi * static_cast<float>(i) / static_cast<float>(segments);
        glVertex2f(cx + std::cos(angle) * radius, cy + std::sin(angle) * radius);
    }
    glEnd();
}

void outlinedCircle(const float cx, const float cy, const float radius, const int segments, const float lineWidth) {
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        const float angle = 2.0F * kPi * static_cast<float>(i) / static_cast<float>(segments);
        glVertex2f(cx + std::cos(angle) * radius, cy + std::sin(angle) * radius);
    }
    glEnd();
}

void ellipse(const float cx, const float cy, const float radiusX, const float radiusY, const int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        const float angle = 2.0F * kPi * static_cast<float>(i) / static_cast<float>(segments);
        glVertex2f(cx + std::cos(angle) * radiusX, cy + std::sin(angle) * radiusY);
    }
    glEnd();
}

void triangle(const Vec2 a, const Vec2 b, const Vec2 c) {
    glBegin(GL_TRIANGLES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glEnd();
}

void polygon(const std::vector<Vec2>& points) {
    if (points.size() < 3U) {
        return;
    }
    glBegin(GL_POLYGON);
    for (const auto& point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void polygon(const std::initializer_list<Vec2> points) {
    polygon(std::vector<Vec2>(points));
}

void line(const Vec2 a, const Vec2 b, const float width) {
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();
}

void star(const float cx, const float cy, const float outerRadius, const float innerRadius, const int points) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= points * 2; ++i) {
        const float angle = -kPi / 2.0F + kPi * static_cast<float>(i) / static_cast<float>(points);
        const float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        glVertex2f(cx + std::cos(angle) * radius, cy + std::sin(angle) * radius);
    }
    glEnd();
}

void cloud(const float x, const float y, const float scale) {
    circle(x - 0.08F * scale, y, 0.075F * scale, 36);
    circle(x, y + 0.035F * scale, 0.10F * scale, 36);
    circle(x + 0.10F * scale, y, 0.08F * scale, 36);
    rectangle(x - 0.10F * scale, y - 0.065F * scale, 0.22F * scale, 0.075F * scale);
}

void text(const float x, const float y, const std::string& value, void* font) {
    if (font == nullptr) {
        font = defaultFont();
    }
    glRasterPos2f(x, y);
    for (const unsigned char character : value) {
        glutBitmapCharacter(font, character);
    }
}

float textWidth(const std::string& value, void* font) {
    if (font == nullptr) {
        font = defaultFont();
    }
    int width = 0;
    for (const unsigned char character : value) {
        width += glutBitmapWidth(font, character);
    }
    return static_cast<float>(width);
}

Color lerp(const Color a, const Color b, const float t) {
    const float clamped = std::clamp(t, 0.0F, 1.0F);
    return {
        a.r + (b.r - a.r) * clamped,
        a.g + (b.g - a.g) * clamped,
        a.b + (b.b - a.b) * clamped,
        a.a + (b.a - a.a) * clamped
    };
}

void verticalGradient(
    const float left,
    const float bottom,
    const float right,
    const float top,
    const Color bottomColor,
    const Color topColor
) {
    glBegin(GL_QUADS);
    setColor(bottomColor);
    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    setColor(topColor);
    glVertex2f(right, top);
    glVertex2f(left, top);
    glEnd();
}

} // namespace yacht::gfx
