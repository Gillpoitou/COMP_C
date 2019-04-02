.text
.global _main
_main:
pushq %rbp
movq    %rsp, %rbp
movl $8, -12(%rbp)
movl -12(%rbp), %eax
movl %eax, -8(%rbp)
movl $2, -20(%rbp)
movl -20(%rbp), %eax
movl %eax, -16(%rbp)
movl -16(%rbp), %edx
movl -8(%rbp), %eax
addl %edx, %eax
movl %eax, -24(%rbp)
movl -24(%rbp), %eax
movl %eax, -4(%rbp)
movl -4(%rbp), %eax
movl %eax, -28(%rbp)
popq    %rbp
ret
