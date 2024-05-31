//
// Created by mspt5 on 24-5-29.
//
#include <string.h>
#include "lcd/lcd.h"

#include "games/play.h"
#include "games/constant.h"
#include "games/objects/wall.h"
#include "games/objects/bird.h"
#include "utils.h"

void show_info() {
    u16 len_h = 1, len_s = 1, m_h = health, m_s = score;
    while (m_h /= 10) len_h++;
    while (m_s /= 10) len_s++;
    LCD_ShowString(0, 0, (u8 *) "score: ", WHITE);
    LCD_ShowNum(72 - 8 * len_s, 0, score, len_s, WHITE);
    LCD_ShowString(0, 20, (u8 *) "life: ", WHITE);
    LCD_ShowNum(72 - 8 * len_h, 20, health, len_h, WHITE);
}

void draw_border() {
    LCD_DrawLine(0, 40, 79, 40, WHITE);
    LCD_DrawLine(0, 159, 79, 159, WHITE);
    LCD_DrawLine(0, 40, 0, 159, WHITE);
    LCD_DrawLine(79, 40, 79, 160, WHITE);
}

void play_loop() {
    u16 last_update = 0;
    // draw player info: health, score
    show_info();
    draw_border();

    // initialize walls
    Wall wall1, wall2;
    InitialWall(&wall1);
    InitialWall(&wall2);
    wall1.last_pos_x = 78;
    wall2.pos_x = 78 + 38;
    wall2.last_pos_x = 78;

    // initialize birds
    Bird bird;
    InitialBird(&bird);

    while (1) {
        // WALL Timer
        if (get_timer_value() - last_update < (1000 / FPS) * SystemCoreClock / 4000) continue;
        last_update = get_timer_value();
        // TODO: draw bird with speed down
        // draw line behind bird
        DrawBird(&bird);
        // draw wall
        DrawWall(&wall1);
        DrawWall(&wall2);

        // update wall
        UpdateWall(&wall1);
        UpdateWall(&wall2);
        // update bird
        UpdateBird(&bird);
        if (Get_Button(V_JOY_CTR) || Get_Button(V_JOY_UP) || Get_Button(V_JOY_DOWN) ||
            Get_Button(V_JOY_LEFT) || Get_Button(V_JOY_RIGHT))
            FlyBird(&bird);

        // TODO: judge too low or too high
        // TODO: judge hit wall
    }
}