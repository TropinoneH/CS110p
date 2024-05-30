//
// Created by mspt5 on 24-5-28.
//
.section .text
.globl startup_scene
.type startup_scene, @function
startup_scene:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 0
    jal LCD_Clear
    lw ra, 0(sp)
    addi sp, sp, 4

    # border of PhH
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 20
    li a1, 0
    li a2, 0
    li a3, 35
    li a4, 65535
    jal LCD_DrawLine
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 500
    jal delay_1ms
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 0
    li a1, 35
    li a2, 20
    li a3, 70
    li a4, 65535
    jal LCD_DrawLine
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 500
    jal delay_1ms
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 20
    li a1, 70
    li a2, 60
    li a3, 70
    li a4, 65535
    jal LCD_DrawLine
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 500
    jal delay_1ms
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 60
    li a1, 70
    li a2, 80
    li a3, 35
    li a4, 65535
    jal LCD_DrawLine
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 500
    jal delay_1ms
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 80
    li a1, 35
    li a2, 60
    li a3, 0
    li a4, 65535
    jal LCD_DrawLine
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 500
    jal delay_1ms
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 60
    li a1, 0
    li a2, 20
    li a3, 0
    li a4, 65535
    jal LCD_DrawLine
    lw ra, 0(sp)
    addi sp, sp, 4

    # pi-band of PhH
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 500
    jal delay_1ms
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 25
    li a1, 5
    li a2, 10
    li a3, 31
    li a4, 65535
    jal LCD_DrawLine
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 55
    li a1, 5
    li a2, 70
    li a3, 31
    li a4, 65535
    jal LCD_DrawLine
    lw ra, 0(sp)
    addi sp, sp, 4

    # mouth
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 33
    li a1, 58
    li a2, 7
    li a3, 65535
    jal LCD_DrawHalfCircle
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 47
    li a1, 58
    li a2, 7
    li a3, 65535
    jal LCD_DrawHalfCircle
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 500
    jal delay_1ms
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 3000
    jal delay_1ms
    lw ra, 0(sp)
    addi sp, sp, 4

    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 0
    jal LCD_Clear
    lw ra, 0(sp)
    addi sp, sp, 4
