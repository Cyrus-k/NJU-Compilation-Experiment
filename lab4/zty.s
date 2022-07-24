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
  
test:
  move $fp, $sp
  addi $sp, $sp, 0
  lw $t0, 8($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, 12($fp)
  move $v0, $t0
  jr $ra
main:
  move $fp, $sp
  addi $sp, $sp, -12
  li $t0, 2
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  li $t0, 1
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  addi $sp, $sp, -8
  sw $fp, 0($sp)
  sw $ra, 4($sp)
  jal test
  move $sp, $fp
  lw $ra, 4($sp)
  lw $fp, 0($sp)
  addi $sp, $sp, 16
  lw $t0, -4($fp)
  move $t0, $v0
  sw $t0, -4($fp)
  lw $t0, -4($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  li $t0, 2
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  li $t0, 1
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  addi $sp, $sp, -8
  sw $fp, 0($sp)
  sw $ra, 4($sp)
  jal test
  move $sp, $fp
  lw $ra, 4($sp)
  lw $fp, 0($sp)
  addi $sp, $sp, 20
  lw $t0, -8($fp)
  move $t0, $v0
  sw $t0, -8($fp)
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  addi $sp, $sp, -8
  sw $fp, 0($sp)
  sw $ra, 4($sp)
  jal test
  move $sp, $fp
  lw $ra, 4($sp)
  lw $fp, 0($sp)
  addi $sp, $sp, 12
  lw $t0, -12($fp)
  move $t0, $v0
  sw $t0, -12($fp)
  lw $t0, -12($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  li $t0, 0
  move $v0, $t0
  jr $ra
