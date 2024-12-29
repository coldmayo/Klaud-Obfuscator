# Example Assembly generated from GCC

## Prolouge

Example:

```
	.section	.rodata
.LC0:
	.string	"Hello World"
.LC1:
	.string	"Goodbye World"
	.text
	.globl	main
	.type	main, @function
```
- read-only data section:
	- .section .rodata declares a read-only data section used for constants
	- .LC0 and .LC1 are labels representing the addresses of the given constants
	- .string "Hello World" and .string "Goodbye World": The strings are stored in the .rodata section
- Code Section initialization:
	- .text: Declares the section for execuatble code
	- .global main: Makes the main function globally visable (So the linker can use it as the program's entry point)
	- .type main, @function: Declares main as a function type

## Actual Code

Example:

```
main:
.LFB0:
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
```
- Function Prologue:
	- main: Indicates the start of the main function
	- .LFB0 and .cfi_*: Debigging and exception-handling metadata
	- pushq %rbp: Saves the base pointer (rbp) of the calling function on the stack
	- movq %rsp, %rbp: Sets up the current function's stack frame by moving the stack pointer (rsp) to the base pointer (rbp)
- Accessing the Strings:
	- leaq .LC0(%rip), %rax: Loads the address of the string "Hello World" (label .LC0) into the rax register. The %rip addressing is used because the string is in a nearby memory location
	- movq %rax, %rdi: Moves the address of the string from rax to rdi. The rdi register is used to pass the first argument to functions in the x86-64 calling convention
	- call puts@PLT: Calls the puts function which prints the string in rdi followed by a newline
- Epolouge:
	- movl $0, %eax: Sets the return value of the main function to 0
	- popq %rbp: Restores the base pointer of the caller

## Metadata

```
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20240910"
	.section	.note.GNU-stack,"",@progbits
```

- .size main, .-main: Specifies the size of the main function for debugging and linking purposes
- .ident: Identifies the GCC compiler version used to generate this assembly
- .section .note.GNU-stack: Marks the stack as non-executable
