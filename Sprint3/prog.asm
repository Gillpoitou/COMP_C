.text
.global _main
_main:
pushq %rbp
movq    %rsp, %rbp
movl $1, -8(%rbp)
movl -8(%rbp), %eax
movl %eax, -4(%rbp)
movl $2, -16(%rbp)
movl -16(%rbp), %eax
movl %eax, -12(%rbp)
movl $3, -24(%rbp)
movl $3, -28(%rbp)
movl -24(%rbp), %edx
movl -28(%rbp), %eax
addl %edx, %eax
movl %eax, -32(%rbp)
movl $3, -36(%rbp)
movl -32(%rbp), %edx
movl -36(%rbp), %eax
addl %edx, %eax
movl %eax, -40(%rbp)
movl $3, -44(%rbp)
movl -40(%rbp), %edx
movl -44(%rbp), %eax
addl %edx, %eax
movl %eax, -48(%rbp)
movl $3, -52(%rbp)
movl -48(%rbp), %edx
movl -52(%rbp), %eax
addl %edx, %eax
movl %eax, -56(%rbp)
movl -56(%rbp), %eax
movl %eax, -20(%rbp)
movl -20(%rbp), %eax
movl %eax, -60(%rbp)
popq    %rbp
ret
