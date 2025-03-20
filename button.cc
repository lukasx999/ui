#include <string>
#include <print>

#include <raylib.h>
#include <raymath.h>

#include "button.hh"

ButtonStateAttribute::ButtonStateAttribute(Color color_bg, Color color_text)
    : m_color_bg(color_bg)
    , m_color_text(color_text)
{}

Button::Button(
    int x,
    int y,
    int width,
    int height,
    ButtonAttributes attrs,
    std::string text,
    float padding
)
    : m_rect(x, y, width, height)
    , m_attrs(attrs)
    , m_text(text)
    , m_padding(std::clamp<float>(padding, 0.0, 0.9))
{
    auto pair = calculate_text_size();
    m_text_width  = std::get<0>(pair);
    m_text_height = std::get<1>(pair);
}

bool Button::clicked() {
    return m_state == ButtonState::Pressed
    && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

ButtonState Button::state() {
    return m_state;
}

Button &Button::operator()() {
    set_state();

    ButtonStateAttribute &attr = m_attrs.at(m_state);

    DrawRectangleRec(m_rect, attr.m_color_bg);
    DrawText(
        m_text.c_str(),
        m_rect.x + m_rect.width  / 2 - m_text_width  / 2.0,
        m_rect.y + m_rect.height / 2 - m_text_height / 2.0,
        m_text_height,
        attr.m_color_text
    );

    return *this;
}

std::pair<int, int> Button::calculate_text_size() {
    int text_height = m_rect.height;
    int text_width = 1e9;

    while (text_width > m_rect.width - m_padding * m_rect.width) {
        text_height--;
        text_width = MeasureText(m_text.c_str(), text_height);
    }

    return { text_width, text_height };
}

void Button::set_state() {
    Vector2 mpos = GetMousePosition();

    m_state = ButtonState::Idle;
    if (CheckCollisionPointRec(mpos, m_rect))
        m_state = IsMouseButtonDown(MOUSE_BUTTON_LEFT)
            ? ButtonState::Pressed
            : ButtonState::Hover;
}

ButtonBuilder &ButtonBuilder::set_x(int x) {
    m_rect.x = x;
    return *this;
}
ButtonBuilder &ButtonBuilder::set_y(int y) {
    m_rect.y = y;
    return *this;
}
ButtonBuilder &ButtonBuilder::set_width(int width) {
    m_rect.width = width;
    return *this;
}

ButtonBuilder &ButtonBuilder::set_height(int height) {
    m_rect.height = height;
    return *this;
}

ButtonBuilder &ButtonBuilder::set_text(std::string text) {
    m_text = text;
    return *this;
}

ButtonBuilder &ButtonBuilder::set_padding(float padding) {
    m_padding = padding;
    return *this;
}

Button ButtonBuilder::build() {

    // TODO: add builder function and add this as default
    ButtonAttributes attrs = {
        { ButtonState::Idle,    ButtonStateAttribute(GRAY, WHITE) },
        { ButtonState::Hover,   ButtonStateAttribute(BLUE, BLACK) },
        { ButtonState::Pressed, ButtonStateAttribute(RED, WHITE) },
    };

    return Button(m_rect.x, m_rect.y, m_rect.width, m_rect.height, attrs, m_text, m_padding);
}
