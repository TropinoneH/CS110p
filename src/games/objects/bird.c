//
// Created by mspt5 on 24-5-31.
//
#include <memory.h>
#include "games/objects/bird.h"
#include "lcd/lcd.h"
#include "games/constant.h"
#include "utils.h"

void InitialBird(Bird *bird) {
    bird->pos_y = 95;
    bird->v_accelerate = 0.2;
    bird->v_speed = 0;

    memset(bird->last_tail, 0, sizeof(u16) * 2 * TailLength);
    memset(bird->tail, 0, sizeof(u16) * 2 * TailLength);
}

void UpdateBird(Bird *bird) {
    bird->v_speed += bird->v_accelerate;
    // update bird
    if (Get_Button(V_JOY_CTR) || Get_Button(V_JOY_UP) || Get_Button(V_JOY_DOWN) ||
        Get_Button(V_JOY_LEFT) || Get_Button(V_JOY_RIGHT))
        bird->v_speed = -2.5;

    bird->pos_y += bird->v_speed;

    // update tail
    for (int i = TailLength - 1; i > 0; i--) {
        bird->last_tail[i][0] = bird->tail[i][0];
        bird->last_tail[i][1] = bird->tail[i][1];

        bird->tail[i][0] = bird->tail[i - 1][0] - 1;
        bird->tail[i][1] = bird->tail[i - 1][1];
    }
    bird->last_tail[0][0] = bird->tail[0][0];
    bird->last_tail[0][1] = bird->tail[0][1];
    bird->tail[0][0] = BIRD_X;
    bird->tail[0][1] = (u16) (int) bird->pos_y;

    if (bird->pos_y < 42 || bird->pos_y > 158) {
        // TODO: health lower
        CleanBird(bird);
        CleanTail(bird);
        InitialBird(bird);
        return;
    }
}

void DrawBird(Bird *bird) {
    if (bird->tail[0][1] < 40 || bird->tail[0][1] > 158) return;
    CleanBird(bird);
    LCD_DrawPoint_big(BIRD_X, bird->tail[0][1], WHITE);
}

void CleanBird(Bird *bird) {
    if (bird->tail[0][1] != bird->last_tail[0][1]) LCD_DrawPoint_big(BIRD_X, bird->last_tail[0][1], BLACK);
}

void DrawTail(Bird *bird) {
    CleanTail(bird);
    for (int i = 0; i < TailLength - 1; i++) {
        if (bird->tail[i][1] == 0 || bird->tail[i + 1][1] == 0)
            continue;

        LCD_DrawLine(bird->tail[i][0], bird->tail[i][1], bird->tail[i + 1][0], bird->tail[i + 1][1], WHITE);
    }
}

void CleanTail(Bird *bird) {
    for (int i = 0; i < TailLength - 1; i++) {
        if (bird->last_tail[i][1] == 0 || bird->last_tail[i + 1][1] == 0)
            continue;

        LCD_DrawLine(bird->last_tail[i][0], bird->last_tail[i][1],
                     bird->last_tail[i + 1][0], bird->last_tail[i + 1][1], BLACK);
    }
}