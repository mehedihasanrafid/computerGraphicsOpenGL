#pragma once

#include <initializer_list>
#include <string>
#include <vector>

namespace yacht::gfx {

struct Color {
    float r;
    float g;
    float b;
    float a{1.0F};
};

struct Vec2 {
    float x;
    float y;
};

void setColor(Color color);
void rectangle(float x, float y, float width, float height);
void outlinedRectangle(float x, float y, float width, float height, float lineWidth = 1.0F);
void circle(float cx, float cy, float radius, int segments = 48);
void outlinedCircle(float cx, float cy, float radius, int segments = 48, float lineWidth = 1.0F);
void ellipse(float cx, float cy, float radiusX, float radiusY, int segments = 48);
void triangle(Vec2 a, Vec2 b, Vec2 c);
void polygon(const std::vector<Vec2>& points);
void polygon(std::initializer_list<Vec2> points);
void line(Vec2 a, Vec2 b, float width = 1.0F);
void star(float cx, float cy, float outerRadius, float innerRadius, int points = 5);
void cloud(float x, float y, float scale = 1.0F);
void text(float x, float y, const std::string& value, void* font = nullptr);
float textWidth(const std::string& value, void* font = nullptr);

Color lerp(Color a, Color b, float t);
void verticalGradient(float left, float bottom, float right, float top, Color bottomColor, Color topColor);

} // namespace yacht::gfx
