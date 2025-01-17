	.text
	.globl	f__25
	.type	f__25, @function
f__25:
.LFB25:
1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	f__2
	call	f__16
	call	f__8
	call	f__13
	call	f__14
	call	f__15
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
		ret
	.cfi_endproc
.LFE25:
	.size	f__25, .-f__25
.file   "test.c"
    .text
    .globl  f__24
    .type   f__24, @function
f__24:
.LFB24:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movl    $0, -20(%rbp)
    movl    $3, -24(%rbp)
    movl    $4, -28(%rbp)
    call    rand
    movl    %eax, %edx
    movslq  %edx, %rax
    imulq   $1717986919, %rax, %rax
    shrq    $32, %rax
    sarq    $31, %rax
    movl    %eax, %ecx
    subl    %ecx, %edx
    testl   %edx, %edx
    jne     .L2
    movl    %edx, -24(%rbp)
    movl    -24(%rbp), %eax
    imull   -28(%rbp), %eax
    movl    %eax, %ebx
    call    rand
    movslq  %eax, %rdx
    imulq   $274877907, %rdx, %rdx
    shrq    $32, %rdx
    sarq    $6, %rdx
    movl    %edx, %ecx
    movl    %eax, %edx
    subl    %ecx, %edx
    imull   $1000, %edx, %ecx
    subl    %ecx, %eax
    movl    %eax, %edx
    leal    (%rbx,%rdx), %eax
    movl    %eax, -20(%rbp)
.L2:
    movl    -20(%rbp), %eax
    movq    %rbx, -8(%rbp)
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE24:
    .size   f__24, .-f__24
.text # dead
	.globl	f__23
	.type	f__23, @function
f__23:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	f__19
	call	f__20
	call	f__21
	call	f__22

	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	f__23, .-f__23
.file	"test.c"
	.text
	.globl	f__22
	.type	f__22, @function
f__22:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	f__22, .-f__22
.file	"test.c"
	.text
	.globl	f__21
	.type	f__21, @function
f__21:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	f__21, .-f__21
.file	"test.c"
	.text
	.globl	f__20
	.type	f__20, @function
f__20:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	f__20, .-f__20
.file	"test.c"
	.text
	.globl	f__19
	.type	f__19, @function
f__19:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	f__19, .-f__19
.text # dead
	.globl	f__18
	.type	f__18, @function
f__18:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	f__17

	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	f__18, .-f__18
.file	"test.c"
	.text
	.globl	f__17
	.type	f__17, @function
f__17:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	f__17, .-f__17
	.text
	.globl	f__16
	.type	f__16, @function
f__16:
.LFB16:
1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
		ret
	.cfi_endproc
.LFE16:
	.size	f__16, .-f__16
.text # dead
	.globl	f__15
	.type	f__15, @function
f__15:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	f__14

	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	f__15, .-f__15
.file	"test.c"
	.text
	.globl	f__14
	.type	f__14, @function
f__14:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	f__14, .-f__14
.file	"test.c"
	.text
    .globl  f_14
    .type   f_14, @function
f_14:
LFB14_:
	.cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
	movl	$2124, -4(%rbp)
	movl	$2, -8(%rbp)
	jmp	.L3
.L3:
	cmp	$0, -8(%rbp)
	jne	.L4
	movl	$5, -12(%rbp)
	jmp	.L5
.L4:
	movl	-4(%rbp), %eax
	imul	%eax, %eax
	movl	%eax, -4(%rbp)
	sub	$1, -8(%rbp)
.L5:
	cmp	$0, -12(%rbp)
	jne	.L6
	movl	-4(%rbp), %eax
	popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.L6:
	movl	-4(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	add	$3, %eax
	add	%eax, -4(%rbp)
	sub	$1, -12(%rbp)

.LFE14_:
    .size   f_14, .-f_14
.text # dead
	.globl	f__13
	.type	f__13, @function
f__13:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	f__9
	call	f__10
	call	f__11
	call	f__12

	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	f__13, .-f__13
.file	"test.c"
	.text
	.globl	f__12
	.type	f__12, @function
f__12:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	f__12, .-f__12
.file	"test.c"
	.text
	.globl	f__11
	.type	f__11, @function
f__11:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	f__11, .-f__11
.file	"test.c"
	.text
	.globl	f__10
	.type	f__10, @function
f__10:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	f__10, .-f__10
.file	"test.c"
	.text
	.globl	f__9
	.type	f__9, @function
f__9:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	f__9, .-f__9
.text # dead
	.globl	f__8
	.type	f__8, @function
f__8:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	f__3
	call	f__4
	call	f__5
	call	f__6
	call	f__7

	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	f__8, .-f__8
.file	"test.c"
	.text
	.globl	f__7
	.type	f__7, @function
f__7:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	f__7, .-f__7
.file	"test.c"
	.text
	.globl	f__6
	.type	f__6, @function
f__6:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	f__6, .-f__6
.file	"test.c"
	.text
	.globl	f__5
	.type	f__5, @function
f__5:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	f__5, .-f__5
.file	"test.c"
	.text
	.globl	f__4
	.type	f__4, @function
f__4:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	f__4, .-f__4
.file	"test.c"
	.text
	.globl	f__3
	.type	f__3, @function
f__3:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	f__3, .-f__3
	.section	.rodata
.LCa:
	.string "w"
.LCb:
	.string "/dev/null"
.LCc:
	.string "Done!"
.LCd:
	.string "/dev/tty"
	.file	"test.c"
	.text
    .globl  f__2
    .type   f__2, @function
f__2:
.LFB2:
    .cfi_startproc
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
	movq    stdout(%rip), %rax
    movq    %rax, %rdx
    leaq    .LCa(%rip), %rsi
    leaq    .LCb(%rip), %rdi
    call    freopen
    leaq    .LCc(%rip), %rdi
    call    puts
    movq    stdout(%rip), %rax
    movq    %rax, %rdx
    leaq    .LCa(%rip), %rsi
    leaq    .LCd(%rip), %rdi
    call    freopen
	movl	$1, %eax
	popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc

.LFE2:
    .size   f__2, .-f__2
	.file	"test.c"
	.text
	.globl	penis
	.type	penis, @function
penis:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	penis, .-penis
	.section	.rodata
.LC0:
	.string	"Hello World"
.LC1:
	.string	"Goodbye World"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	f__18
	call	f__23
	call	f__25
	call	f__24
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20240910"
	.section	.note.GNU-stack,"",@progbits
