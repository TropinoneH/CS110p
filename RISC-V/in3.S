.data
# length of image matrix (number of columns)
.globl image_length
image_length:
    .word 5
# width of image matrix (number of rows)
.globl image_width
image_width:
    .word 5
# image matrix values
.globl image
image:
    .word 14, 17, 23, -30, -27, 29, -27, 9, -21, -11, -9, 20, 6, -7, -24, -6, -6, -18, 28, -29, 8, 9, -7, 16, -6

# length of kernel matrix (kernel is square, so length and width are the same)
.globl kernel_length
kernel_length:
    .word 3
# width of kernel matrix
.globl kernel_width
kernel_width:
    .word 3
# kernel matrix values
.globl kernel
kernel:
    .word 1, 5, 9, 8, 9, 4, 3, 0, 3
