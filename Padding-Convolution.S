.import "./RISC-V/in3.S"

.text
main:
    la s0 image_length
    la s1 image_width
    la s2 kernel_length
    la s3 kernel_width
    # img_col
    lw s0 0(s0)
    # img_row
    lw s1 0(s1)
    # kernel_col
    lw s2 0(s2)
    # kernel_row
    lw s3 0(s3)
    # s4 = image_row - kernel_row + 1
    addi s4 s1 1
    sub s4 s4 s3
    # s5 = image_col - kernel_col + 1
    addi s5 s0 1
    sub s5 s5 s2
    # padding, rol_padding = col_padding(kernel will be square and length will be odd)
    addi s9 s2 -1
    srai s9 s9 1
    add t0 s9 s9
    add s4 s4 t0
    add s5 s5 t0
    # image address
    la s6 image
    # kernel address
    la s7 kernel
    # bytes of .word
    li s8 4
    # i in loop_out_row
    li t0 0
    # j in loop_out_col
    li t1 0
    # ki in loop_kernel_row
    li t2 0
    # kj in loop_kernel_col
    li t3 0

loop_out_row:
    beq t0 s4 end
    jal loop_out_col_init
    addi t0 t0 1
    j loop_out_row

loop_out_col_init:
    addi sp sp -4
    sw ra 0(sp)

loop_out_col:
    beq t1 s5 end_out_col
    jal loop_kernel_row_init
    addi t1 t1 1
    j loop_out_col

loop_kernel_row_init:
    addi sp sp -4
    sw ra 0(sp)
    li a1 0

loop_kernel_row:
    beq t2 s3 end_kernel_row
    jal loop_kernel_col_init
    addi t2 t2 1
    j loop_kernel_row

loop_kernel_col_init:
    addi sp sp -4
    sw ra 0(sp)

loop_kernel_col:
    beq t3 s2    end_kernel_col
    # calculate the index of image and kernel
    # image index = (i + ki) * image_col + (j + kj)
    add a2 t0 t2
    add a3 t1 t3
    # calc image pixel, if col=0/cols or row=0/rows, then return 0
    # or, it will return image[row-1][col-1]
    addi sp sp -16
    sw t0 0(sp)
    sw t1 4(sp)
    sw t2 8(sp)
    sw t3 12(sp)
    jal get_image_pixel
    lw t0 0(sp)
    lw t1 4(sp)
    lw t2 8(sp)
    lw t3 12(sp)
    addi sp sp 16
    add t4 x0 a2
    # kernel index = ki * kernel_col + kj
    mul t5 t2 s2
    add t5 t5 t3
    # load kernel
    mul t5 t5 s8
    add t5 t5 s7
    lw t5 0(t5)
    # calculate the output
    mul t4 t4 t5
    add a1 a1 t4
    addi t3 t3 1
    j loop_kernel_col

end_kernel_col:
    lw ra 0(sp)
    addi sp sp 4
    li t3 0
    ret

end_kernel_row:
    lw ra 0(sp)
    addi sp sp 4
    li t2 0
    # already calculated the output, store it in a1
    li a0 1
    ecall
    li a0 11
    li a1 32
    ecall
    ret

end_out_col:
    lw ra 0(sp)
    addi sp sp 4
    li t1 0
    li a0 11
    li a1 10
    ecall
    ret

end:
    li a0 10
    ecall

get_image_pixel:
    # row_padding = col_padding
    # row < row_padding
    slt t0 a2 s9
    # ans_row - row_padding < row
    slt t1 s1 a2
    # col < padding
    slt t2 a3 s9
    # ans_col - padding < col
    slt t3 s0 a3
    # if row=0 or row=img_row or col=0 or col=img_col, return 0
    bnez t0 padding_pixel
    bnez t1 padding_pixel
    bnez t2 padding_pixel
    bnez t3 padding_pixel
    # else => truth pixel => return image[row-padding][col-padding]
    sub a2 a2 s9
    sub a3 a3 s9
    # index = (i + ki) * image_col + (j + kj)
    # image_col = padding_image_col - 2
    mul a2 a2 s0
    add a2 a2 a3
    mul a2 a2 s8
    add a2 a2 s6
    lw a2 0(a2)
    ret

padding_pixel:
    li a2 0
    ret