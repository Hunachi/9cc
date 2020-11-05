.intel_syntax noprefix
.globl main
main:
  push 1
  push 5
  push 0
  push 5
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rax
  ret
