//
// Created by mspt5 on 24-5-31.
//
#include <math.h>
#include "lcd/lcd.h"

#include "games/objects/wall.h"
#include "games/constant.h"

void UpdateWall(Wall *wall) {
    // different speed for different level
    wall->last_pos_x = wall->pos_x <= 78 ? wall->pos_x : 78;
    wall->pos_x -= cur_level == 2 ? 1 : 0.5;

    if (wall->pos_x <= 1) {
        InitialWall(wall);
    }
}

void DrawWall(Wall *wall) {
    int x = (int) wall->pos_x, lx = (int) wall->last_pos_x;
    if (wall->pos_x > 78 || x == lx) return;
    LCD_DrawLine(x, 41, x, wall->pos_y, WHITE);
    LCD_DrawLine(x, wall->pos_y + wall->width, x, 158, WHITE);

    LCD_DrawLine(lx, 41, lx, 158, BLACK);
}

void InitialWall(Wall *wall) {
    wall->pos_y = 50 + rand() % 50;
    wall->width = (4 - cur_level) * 10;
    wall->pos_x = 78;
}