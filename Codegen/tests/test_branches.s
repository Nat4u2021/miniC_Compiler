	.file	"test_branches.c"
	.text
	.globl	func
	.type	func, @function
func:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	cmpl	$100, 8(%ebp)
	jle	.L2
	movl	$10, -8(%ebp)
	movl	$20, -4(%ebp)
	jmp	.L3
.L2:
	movl	$100, -8(%ebp)
	movl	$200, -4(%ebp)
.L3:
	movl	8(%ebp), %edx
	movl	-8(%ebp), %eax
	addl	%edx, %eax
	leave
	ret
