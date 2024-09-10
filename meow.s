	.text
	.globl main
main:
	movl	$4, %eax

	cmpl	$0, %eax
	movl	$0, %eax
	sete	%al

	cmpl	$0, %eax
	movl	$0, %eax
	sete	%al

	cmpl	$0, %eax
	movl	$0, %eax
	sete	%al

	cmpl	$0, %eax
	movl	$0, %eax
	sete	%al

	not	%eax

	ret

