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
    uint64_t up = 0;
    uint64_t down = 0;
    draw_menu(cur_level);
    while (!Get_Button(JOY_CTR)) {
        if (Get_Button(V_JOY_UP)) {
            if (get_timer_value() - up < SystemCoreClock / 4000 * 300) continue;
            up = get_timer_value();
            cur_level = cur_level == 0 ? 3 : cur_level - 1;
            draw_menu(cur_level);
        } else if (Get_Button(V_JOY_DOWN)) {
            if (get_timer_value() - down < SystemCoreClock / 4000 * 300) continue;
            down = get_timer_value();
            cur_level = cur_level == 3 ? 0 : cur_level + 1;
            draw_menu(cur_level);
        }
    }

    if (cur_level == 3) {
        if (startup_scene(0)) exit(1);
        choose_level();
    }
}

