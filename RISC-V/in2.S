.data
# length of image matrix
.globl image_length
image_length:
	.word 5
# width of image matrix
.globl image_width
image_width:
	.word 5
.globl image
image:
    .word 60 113 56 139 85 73 121 54 84 128 131 99 70 129 127 80 57 115 69 134 104 126 123 95 130
# length of kernel matrix
.globl kernel_length
kernel_length:
	.word 3
# width of kernel matrix
.globl kernel_width
kernel_width:
	.word 3
.globl kernel
kernel:
    .word 0 -1 0 -1 5 -1 0 -1 0
    # .word 0 0 0 0 -1 0 0 0 0
