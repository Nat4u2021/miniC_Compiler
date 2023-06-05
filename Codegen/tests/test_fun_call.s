	.file	"test_fun_call.c"
	.text
	.globl	func
	.type	func, @function
func:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	read@PLT
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	subl	$12, %esp
	pushl	-16(%ebp)
	call	print@PLT
	addl	$16, %esp
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret
