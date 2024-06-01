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

void debug_info(Bird *bird) {
    if (bird == NULL) {
        LCD_ShowNum(72 - 8, 0, 0, 1, WHITE);
        LCD_ShowNum(72 - 8, 20, 0, 1, WHITE);
        return;
    }
    u16 l = 1, ll = 1, n = bird->tail[0][1], nn = bird->tail[1][1];
    while (n /= 10)l++;
    while (nn /= 10)ll++;
    LCD_Fill(0, 0, 80, 39, BLACK);
    LCD_ShowNum(72 - 8 * l, 0, bird->tail[0][1], l, WHITE);
    LCD_ShowNum(72 - 8 * ll, 20, bird->tail[1][1], ll, WHITE);
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
    if (cur_level == 3) debug_info(NULL); else show_info();
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
        if (get_timer_value() - last_update < ((cur_level == 3) ? 100 : (1000 / FPS)) * (SystemCoreClock / 4000))
            continue;
        last_update = get_timer_value();

        // Debug mode
        if (cur_level == 3 && !Get_Button(BUTTON_1)) continue;
        if (cur_level == 3) debug_info(&bird); else show_info();

        // draw line behind bird
        DrawBird(&bird);
        // draw wall
        DrawWall(&wall1);
        DrawWall(&wall2);
        // draw bird with tail
        DrawTail(&bird);

        // update wall
        UpdateWall(&wall1);
        UpdateWall(&wall2);
        // update bird
        UpdateBird(&bird);

        // TODO: judge too low or too high
        // TODO: judge hit wall
    }
}