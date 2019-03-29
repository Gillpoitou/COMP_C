pushq %rbp
movq    %rsp, %rbp
movl $3, -4(%rbp)
movl $4, -8(%rbp)
movl -4(%rbp), %eax
movl %eax, -12(%rbp)
movl -16(%rbp), %eax
popq    %rbp
ret
