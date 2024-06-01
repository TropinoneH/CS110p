//
// Created by mspt5 on 24-5-31.
//

#ifndef PROJ3_BIRD_H
#define PROJ3_BIRD_H

#include "lcd/lcd.h"
#include <stdbool.h>

#define TailLength 15

typedef struct {
    double v_speed;
    double v_accelerate;
    double pos_y;

    u16 tail[TailLength][2];
    u16 last_tail[TailLength][2];

    double alive_time;
    bool invincible;
} Bird;

void UpdateBird(Bird *bird);

void InitialBird(Bird *bird);

void DrawBird(Bird *bird);

void CleanBird(Bird *bird);

void DrawTail(Bird *bird);

void CleanTail(Bird *bird);

void FlyBird(Bird *bird);

#endif //PROJ3_BIRD_H
