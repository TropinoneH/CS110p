//
// Created by mspt5 on 24-5-31.
//

#ifndef PROJ3_BIRD_H
#define PROJ3_BIRD_H

#include "lcd/lcd.h"

typedef struct {
    double v_speed;
    double v_accelerate;
    double pos_y;
    double last_pos_y;
    double falling_time;
} Bird;

void UpdateBird(Bird *bird);

void InitialBird(Bird *bird);

void DrawBird(Bird *bird);

void FlyBird(Bird *bird);

#endif //PROJ3_BIRD_H
