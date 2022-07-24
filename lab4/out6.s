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
  
fact:
  move $fp, $sp
  addi $sp, $sp, -16
  lw $t0, -4($fp)
  li $t1, 1
  move $t0, $t1
  sw $t0, -4($fp)
  lw $t0, -8($fp)
  li $t1, 1
  move $t0, $t1
  sw $t0, -8($fp)
label1:
  lw $t0, -8($fp)
  lw $t1, 8($fp)
  ble $t0, $t1, label2
  j label3
label2:
  lw $t0, -12($fp)
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  mul $t0, $t1, $t2
  sw $t0, -12($fp)
  lw $t0, -4($fp)
  lw $t1, -12($fp)
  move $t0, $t1
  sw $t0, -4($fp)
  lw $t0, -16($fp)
  lw $t1, -8($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -16($fp)
  lw $t0, -8($fp)
  lw $t1, -16($fp)
  move $t0, $t1
  sw $t0, -8($fp)
  j label1
label3:
  lw $t0, -4($fp)
  move $v0, $t0
  jr $ra
main:
  move $fp, $sp
  addi $sp, $sp, -56
  lw $t0, -24($fp)
  li $t1, 0
  move $t0, $t1
  sw $t0, -24($fp)
  lw $t0, -28($fp)
  li $t1, 5
  move $t0, $t1
  sw $t0, -28($fp)
label4:
  lw $t0, -24($fp)
  lw $t1, -28($fp)
  blt $t0, $t1, label5
  j label6
label5:
  lw $t0, -32($fp)
  lw $t1, -24($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -32($fp)
  lw $t0, -36($fp)
  addi $t1, $fp, -20
  lw $t2, -32($fp)
  add $t0, $t1, $t2
  sw $t0, -36($fp)
  lw $t0, -40($fp)
  lw $t1, -24($fp)
  li $t2, 2
  add $t0, $t1, $t2
  sw $t0, -40($fp)
  lw $t0, -36($fp)
  lw $t1, -40($fp)
  sw $t1, 0($t0)
  lw $t0, -44($fp)
  lw $t1, -24($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  sw $t0, -44($fp)
  lw $t0, -48($fp)
  addi $t1, $fp, -20
  lw $t2, -44($fp)
  add $t0, $t1, $t2
  sw $t0, -48($fp)
  lw $t0, -48($fp)
  lw $t1, 0($t0)
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  addi $sp, $sp, -8
  sw $fp, 0($sp)
  sw $ra, 4($sp)
  jal fact
  move $sp, $fp
  lw $ra, 4($sp)
  lw $fp, 0($sp)
  addi $sp, $sp, 12
  lw $t0, -52($fp)
  move $t0, $v0
  sw $t0, -52($fp)
  lw $t0, -52($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -56($fp)
  lw $t1, -24($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -56($fp)
  lw $t0, -24($fp)
  lw $t1, -56($fp)
  move $t0, $t1
  sw $t0, -24($fp)
  j label4
label6:
  li $t0, 0
  move $v0, $t0
  jr $ra
