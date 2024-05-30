#include "lcd/m_lcd.h"

void LCD_DrawHalfCircle(u16 x0, u16 y0, u8 r, u16 color) {
    int a, b;
    // int di;
    a = 0;
    b = r;
    while (a <= b) {
//        LCD_DrawPoint(x0-b,y0-a,color);             //3
//        LCD_DrawPoint(x0+b,y0-a,color);             //0
        LCD_DrawPoint(x0 - a, y0 + b, color);             //1
//        LCD_DrawPoint(x0-a,y0-b,color);             //2
        LCD_DrawPoint(x0 + b, y0 + a, color);             //4
//        LCD_DrawPoint(x0+a,y0-b,color);             //5
        LCD_DrawPoint(x0 + a, y0 + b, color);             //6
        LCD_DrawPoint(x0 - b, y0 + a, color);             //7
        a++;
        if ((a * a + b * b) > (r * r))//Determine whether the points to be drawn are too far away
        {
            b--;
        }
    }
}
