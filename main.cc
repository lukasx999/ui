#include <print>
#include <string>

#include <raylib.h>
#include <raymath.h>

#include "button.hh"
#include "switch.hh"

constexpr int width  = 1600;
constexpr int height = 900;


int main() {

    InitWindow(width, height, "UI");
    SetTargetFPS(60);

    int btn_w = 500, btn_h = 200;

    ButtonAttributes btn_attrs = {
        { ButtonState::Idle,    ButtonStateAttribute(GRAY, WHITE) },
        { ButtonState::Hover,   ButtonStateAttribute(BLUE, BLACK) },
        { ButtonState::Pressed, ButtonStateAttribute(RED, WHITE) },
    };

    Button btn1(
        width / 2 - btn_w / 2,
        (height / 2 - btn_h / 2) - btn_h,
        btn_w,
        btn_h,
        btn_attrs,
        "click me",
        0.3
    );

    Button btn2(
        width / 2 - btn_w / 2,
        (height / 2 - btn_h / 2) + btn_h,
        btn_w,
        btn_h,
        btn_attrs,
        "this is a button",
        0.5
    );

    Switch sw(100, height/2, 300, 200, 0.75, GRAY, RED);

    auto btn = ButtonBuilder()
        .set_height(300)
        .set_width(500)
        .set_x(0)
        .set_y(0)
        .set_padding(0.3)
        .set_text("hello")
        .build();

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);

            btn();

            sw();

            if (btn1().clicked()) {
                std::println("button 1 was clicked!");
            }

            if (btn2().clicked()) {
                std::println("button 2 was clicked!");
            }

        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
