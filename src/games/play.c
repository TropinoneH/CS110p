//
// Created by mspt5 on 24-5-29.
//
#include <string.h>
#include "lcd/lcd.h"

#include "games/play.h"
#include "games/constant.h"

void show_info() {
    u16 len_h = 1, len_s = 1, m_h = health, m_s = score;
    while (m_h /= 10) len_h++;
    while (m_s /= 10) len_s++;
    LCD_ShowString(0, 0, (u8 *)"score: ", WHITE);
    LCD_ShowNum(72 - 8 * len_s, 0, score, len_s, WHITE);
    LCD_ShowString(0, 20, (u8 *)"life: ", WHITE);
    LCD_ShowNum(72 - 8 * len_h, 20, health, len_h, WHITE);
}

void play_loop() {
    // draw player info: health, score
    show_info();
    // TODO: draw bird with speed down
    // TODO: draw line behind bird
    // TODO: draw wall

    // TODO: judge too low or too high
    // TODO: judge hit wall
}