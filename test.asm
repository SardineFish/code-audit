.data
glob: .word 0


.text
__start:
move $fp, $sp
main:
sub $sp, $sp, 68
move $fp, $sp
        # PUSH $ra
sub $sp, $sp, 4
sw $ra, 0($sp)
add $t0, $fp, 0
li $t1, 1
sw $t1, 0($t0)
li $t2, 6
sw $t2, 4($t0)
li $t3, 7
sw $t3, 8($t0)
li $t1, 2
sw $t1, 12($t0)
li $t2, 6
sw $t2, 16($t0)
li $t3, 9
sw $t3, 20($t0)
li $t1, 3
sw $t1, 24($t0)
li $t2, 5
sw $t2, 28($t0)
li $t3, 4
sw $t3, 32($t0)
li $t1, 7
sw $t1, 36($t0)
add $t2, $fp, 40
li $t3, 10
sw $t3, 0($t2)
add $t1, $fp, 44
li $v0, 5
syscall
sw $v0, 0($t1)
add $t0, $fp, 48
li $v0, 5
syscall
sw $v0, 0($t0)
add $t3, $fp, 52
        # PUSH $t0
sub $sp, $sp, 4
sw $t0, 0($sp)
        # PUSH $t1
sub $sp, $sp, 4
sw $t1, 0($sp)
        # PUSH $t2
sub $sp, $sp, 4
sw $t2, 0($sp)
        # PUSH $t3
sub $sp, $sp, 4
sw $t3, 0($sp)
        # PUSH $fp
sub $sp, $sp, 4
sw $fp, 0($sp)
sub $t2, $sp, 8
lw $t1, 44($fp)
sw $t1, 0($t2)
lw $t0, 48($fp)
sw $t0, 4($t2)
jal gcd
        # POP $fp
lw $fp, 0($sp)
add $sp, $sp, 4
        # POP $t3
lw $t3, 0($sp)
add $sp, $sp, 4
        # POP $t2
lw $t2, 0($sp)
add $sp, $sp, 4
        # POP $t1
lw $t1, 0($sp)
add $sp, $sp, 4
        # POP $t0
lw $t0, 0($sp)
add $sp, $sp, 4
sw $v0, 0($t3)
lw $a0, 52($fp)
li $v0, 1
syscall
add $t1, $fp, 56
li $t0, 0
sw $t0, 0($t1)
Loop_7:
lw $t3, 40($fp)
lw $t0, 56($fp)
slt $t2, $t0, $t3
beqz $t2, Label_9
add $t1, $fp, 60
li $t0, 0
sw $t0, 0($t1)
Loop_10:
lw $t2, 56($fp)
lw $t0, 40($fp)
sub $t3, $t0, $t2
sub $t1, $t3, 1
lw $t2, 60($fp)
slt $t0, $t2, $t1
beqz $t0, Label_12
lw $t2, 60($fp)
mul $t3, $t2, 4
add $t1, $fp, 0
add $t1, $t1, $t3
lw $t2, 60($fp)
add $t0, $t2, 1
mul $t3, $t0, 4
add $t2, $fp, 0
add $t2, $t2, $t3
lw $t2, 0($t2)
lw $t1, 0($t1)
slt $t0, $t1, $t2
beqz $t0, Label_13
lw $t1, 60($fp)
mul $t3, $t1, 4
add $t2, $fp, 0
add $t2, $t2, $t3
lw $t2, 0($t2)
add $t1, $fp, 64
sw $t2, 0($t1)
lw $t1, 60($fp)
mul $t3, $t1, 4
add $t0, $fp, 0
add $t0, $t0, $t3
lw $t1, 60($fp)
add $t2, $t1, 1
mul $t3, $t2, 4
add $t1, $fp, 0
add $t1, $t1, $t3
lw $t1, 0($t1)
sw $t1, 0($t0)
lw $t0, 60($fp)
add $t3, $t0, 1
mul $t2, $t3, 4
add $t1, $fp, 0
add $t1, $t1, $t2
lw $t3, 64($fp)
sw $t3, 0($t1)
j Label_14
Label_13:
Label_14:
lw $t1, 60($fp)
lw $t2, 60($fp)
addi $t2, $t2, 1
sw $t2, 60($fp)
j Loop_10
Label_12:
lw $t3, 56($fp)
lw $t0, 56($fp)
addi $t0, $t0, 1
sw $t0, 56($fp)
j Loop_7
Label_9:
li $v0, 10
syscall
gcd:
sub $sp, $sp, 8
move $fp, $sp
        # PUSH $ra
sub $sp, $sp, 4
sw $ra, 0($sp)
lw $t1, 4($fp)
lw $t2, 0($fp)
div $t0, $t2, $t1
mfhi $t0
seq $t3, $t0, 0
beqz $t3, Label_4
lw $v0, 4($fp)
        # POP $ra
lw $ra, 0($sp)
add $sp, $sp, 4
add $sp, $sp, 8
lw $v0, 4($fp)
jr $ra    # return
j Label_5
Label_4:
Label_5:
        # PUSH $t0
sub $sp, $sp, 4
sw $t0, 0($sp)
        # PUSH $t1
sub $sp, $sp, 4
sw $t1, 0($sp)
        # PUSH $t2
sub $sp, $sp, 4
sw $t2, 0($sp)
        # PUSH $t3
sub $sp, $sp, 4
sw $t3, 0($sp)
        # PUSH $fp
sub $sp, $sp, 4
sw $fp, 0($sp)
sub $t2, $sp, 8
lw $t1, 4($fp)
sw $t1, 0($t2)
lw $t3, 4($fp)
lw $t1, 0($fp)
div $t0, $t1, $t3
mfhi $t0
sw $t0, 4($t2)
jal gcd
        # POP $fp
lw $fp, 0($sp)
add $sp, $sp, 4
        # POP $t3
lw $t3, 0($sp)
add $sp, $sp, 4
        # POP $t2
lw $t2, 0($sp)
add $sp, $sp, 4
        # POP $t1
lw $t1, 0($sp)
add $sp, $sp, 4
        # POP $t0
lw $t0, 0($sp)
add $sp, $sp, 4
        # POP $ra
lw $ra, 0($sp)
add $sp, $sp, 4
add $sp, $sp, 8
jr $ra    # return
