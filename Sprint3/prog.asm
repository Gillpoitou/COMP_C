pushq %rbp
movq    %rsp, %rbp
movl $3, -4(%rbp)
movl $4, -8(%rbp)
movl -4(%rbp), %eax
movl %eax, -12(%rbp)
movl -8(%rbp), %edx
movl -4(%rbp), %eax
addl %edx, %eax
movl %eax, -16(%rbp)
movl -4(%rbp), %eax
addl $4, %eax
movl %eax, -12(%rbp)
movl -16(%rbp), %eax
addl $5, %eax
movl %eax, -20(%rbp)
movl $9, -8(%rbp)
movl -16(%rbp), %eax
popq    %rbp
ret
