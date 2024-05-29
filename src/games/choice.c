//
// Created by mspt5 on 24-5-28.
//

#include "games/choice.h"
#include "lcd/lcd.h"
#include "utils.h"
#include "stdbool.h"

#include "games/constant.h"
#include "games/startup.h"

void draw_menu(int level) {
    LCD_ShowString(22, 0, (u8 *) "easy", level == 0 ? WHITE : GRAY);
    LCD_ShowString(16, 20, (u8 *) "normal", level == 1 ? WHITE : GRAY);
    LCD_ShowString(22, 40, (u8 *) "hard", level == 2 ? WHITE : GRAY);
    LCD_ShowString(18, 80, (u8 *) "debug", level == 3 ? BROWN : GRAY);
}

void choose_level() {
    bool hold = false;
    draw_menu(cur_level);
    while (!Get_Button(JOY_CTR)) {
        if (Get_Button(V_JOY_UP) && cur_level && !hold) {
            hold = true;
            cur_level -= 1;
            draw_menu(cur_level);
        } else if (Get_Button(V_JOY_DOWN) && cur_level != 3 && !hold) {
            hold = true;
            cur_level += 1;
            draw_menu(cur_level);
        }

        if (!Get_Button(V_JOY_UP) && !Get_Button(V_JOY_DOWN)) hold = false;
    }

    if (cur_level == 3) {
        startup_scene();
        choose_level();
    }
}

