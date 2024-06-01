//
// Created by mspt5 on 24-5-31.
//
#include "games/objects/bird.h"
#include "lcd/lcd.h"
#include "games/constant.h"

void InitialBird(Bird *bird) {
    bird->pos_y = 95;
    bird->v_accelerate = 0.1;
    bird->v_speed = 2;
    bird->falling_time = 0;
}

void UpdateBird(Bird *bird) {
    bird->falling_time += 1.0 / FPS;
    bird->v_speed += bird->v_accelerate * bird->falling_time;

    bird->last_pos_y = bird->pos_y;

    bird->pos_y += bird->v_speed;

    if (bird->pos_y < 44 || bird->pos_y > 156) {
        // TODO: health lower
        InitialBird(bird);
    }
}

void DrawBird(Bird *bird) {
    int y = (int) bird->pos_y, ly = (int) bird->last_pos_y;
    if (y < 44 || y > 156) return;
    if (y != ly) LCD_DrawPoint_big(BIRD_X, ly, BLACK);
    LCD_DrawPoint_big(BIRD_X, y, WHITE);
}

void FlyBird(Bird * bird) {
    bird->v_speed = 0;
    bird->v_speed = 1;
    bird->falling_time = 0;


    bird->pos_y -= 2.5;

    if (bird->pos_y < 42) {
        // TODO: health lower
        bird->debug = (u16) bird->pos_y;
        InitialBird(bird);
    }
}