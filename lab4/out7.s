.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra
write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra
  
main:
  move $fp, $sp
  addi $sp, $sp, -136
  lw $t0, -24($fp)
  li $t1, 0
  move $t0, $t1
  sw $t0, -24($fp)
  lw $t0, -28($fp)
  li $t1, 5
  move $t0, $t1
  sw $t0, -28($fp)
  lw $t0, -32($fp)
  li $t1, 0
  move $t0, $t1
  sw $t0, -32($fp)
label1:
  lw $t0, -24($fp)
  li $t1, 5
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -36($fp)
  lw $t1, -24($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -36($fp)
  lw $t0, -40($fp)
  addi $t1, $fp, -20
  lw $t2, -36($fp)
  add $t0, $t1, $t2
  sw $t0, -40($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -44($fp)
  move $t0, $v0
  sw $t0, -44($fp)
  lw $t0, -40($fp)
  lw $t1, -44($fp)
  sw $t1, 0($t0)
  lw $t0, -48($fp)
  lw $t1, -24($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -48($fp)
  lw $t0, -24($fp)
  lw $t1, -48($fp)
  move $t0, $t1
  sw $t0, -24($fp)
  j label1
label3:
  lw $t0, -24($fp)
  lw $t1, -28($fp)
  move $t0, $t1
  sw $t0, -24($fp)
label4:
  lw $t0, -24($fp)
  li $t1, 0
  bgt $t0, $t1, label5
  j label6
label5:
label7:
  lw $t0, -52($fp)
  lw $t1, -24($fp)
  li $t2, 1
  sub $t0, $t1, $t2
  sw $t0, -52($fp)
  lw $t0, -32($fp)
  lw $t1, -52($fp)
  blt $t0, $t1, label8
  j label9
label8:
  lw $t0, -56($fp)
  lw $t1, -32($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -56($fp)
  lw $t0, -60($fp)
  addi $t1, $fp, -20
  lw $t2, -56($fp)
  add $t0, $t1, $t2
  sw $t0, -60($fp)
  lw $t0, -64($fp)
  lw $t1, -32($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -64($fp)
  lw $t0, -68($fp)
  lw $t1, -64($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -68($fp)
  lw $t0, -72($fp)
  addi $t1, $fp, -20
  lw $t2, -68($fp)
  add $t0, $t1, $t2
  sw $t0, -72($fp)
  lw $t0, -60($fp)
  lw $t1, 0($t0)
  lw $t0, -72($fp)
  lw $t2, 0($t0)
  bgt $t1, $t2, label10
  j label11
label10:
  lw $t0, -76($fp)
  lw $t1, -32($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -76($fp)
  lw $t0, -80($fp)
  addi $t1, $fp, -20
  lw $t2, -76($fp)
  add $t0, $t1, $t2
  sw $t0, -80($fp)
  lw $t0, -84($fp)
  lw $t1, -80($fp)
  lw $t2, 0($t1)
  move $t0, $t2
  sw $t0, -84($fp)
  lw $t0, -88($fp)
  lw $t1, -32($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -88($fp)
  lw $t0, -92($fp)
  addi $t1, $fp, -20
  lw $t2, -88($fp)
  add $t0, $t1, $t2
  sw $t0, -92($fp)
  lw $t0, -96($fp)
  lw $t1, -32($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -96($fp)
  lw $t0, -100($fp)
  lw $t1, -96($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -100($fp)
  lw $t0, -104($fp)
  addi $t1, $fp, -20
  lw $t2, -100($fp)
  add $t0, $t1, $t2
  sw $t0, -104($fp)
  lw $t0, -92($fp)
  lw $t1, -104($fp)
  lw $t2, 0($t1)
  sw $t2, 0($t0)
  lw $t0, -108($fp)
  lw $t1, -32($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -108($fp)
  lw $t0, -112($fp)
  lw $t1, -108($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -112($fp)
  lw $t0, -116($fp)
  addi $t1, $fp, -20
  lw $t2, -112($fp)
  add $t0, $t1, $t2
  sw $t0, -116($fp)
  lw $t0, -116($fp)
  lw $t1, -84($fp)
  sw $t1, 0($t0)
label11:
  lw $t0, -120($fp)
  lw $t1, -32($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -120($fp)
  lw $t0, -32($fp)
  lw $t1, -120($fp)
  move $t0, $t1
  sw $t0, -32($fp)
  j label7
label9:
  lw $t0, -32($fp)
  li $t1, 0
  move $t0, $t1
  sw $t0, -32($fp)
  lw $t0, -124($fp)
  lw $t1, -24($fp)
  li $t2, 1
  sub $t0, $t1, $t2
  sw $t0, -124($fp)
  lw $t0, -24($fp)
  lw $t1, -124($fp)
  move $t0, $t1
  sw $t0, -24($fp)
  j label4
label6:
  lw $t0, -24($fp)
  li $t1, 0
  move $t0, $t1
  sw $t0, -24($fp)
label12:
  lw $t0, -24($fp)
  li $t1, 5
  blt $t0, $t1, label13
  j label14
label13:
  lw $t0, -128($fp)
  lw $t1, -24($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -128($fp)
  lw $t0, -132($fp)
  addi $t1, $fp, -20
  lw $t2, -128($fp)
  add $t0, $t1, $t2
  sw $t0, -132($fp)
  lw $t0, -132($fp)
  lw $t1, 0($t0)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -136($fp)
  lw $t1, -24($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -136($fp)
  lw $t0, -24($fp)
  lw $t1, -136($fp)
  move $t0, $t1
  sw $t0, -24($fp)
  j label12
label14:
  li $t0, 0
  move $v0, $t0
  jr $ra
