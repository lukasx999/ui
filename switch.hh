#pragma once

#include <print>

#include <raylib.h>
#include <raymath.h>

#include "ui.hh"

class Switch : public Element {
    bool m_state;
    float m_padding;
    Color m_color_bg;
    Color m_color_circle;
public:
    Switch(int x, int y, int width, int height, float padding, Color color_bg, Color color_circle);
    Switch &update();
private:
    void set_state();
};
