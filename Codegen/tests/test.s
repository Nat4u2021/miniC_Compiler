	.file	"test.c"
	.text
	.globl	func
	.type	func, @function
func:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$10, -4(%ebp)
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	cmpl	$100, %eax
	jg	.L2
	jmp .L4

.L4:
	movl	-4(%ebp), %eax
	addl	$100, %eax
	movl	%eax, -8(%ebp)
	jmp	.L3
.L2:
	movl	-4(%ebp), %eax
	addl	$20, %eax
	movl	%eax, -8(%ebp)
.L3:
	movl	-8(%ebp), %eax
	leave
	ret
