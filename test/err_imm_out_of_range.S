lb x0 2048(x0)
lb x0 -2049(x0)
addi x0 x0 2048
addi x0 x0 -2049
sb x0 2048(x0)
sb x0 -2049(x0)
beq x0 x0 4096
beq x0 x0 -4097
auipc x0 1048576
auipc x0 -1
jal x0 1048576
jal x0 -1048577
beqz x0 4096
beqz x0 -4097
bnez x0 4096
bnez x0 -4097
j 1048576
j -1048577