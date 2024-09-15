	.text
	.globl _main
_main:
	movl	$24, %eax
	

	cmpl	$0, %eax
	movq	$0, %rax
	setne	%al
	je	end0
	movl	$1, %eax
	
cmpl	$0, %eax
	setne	%al
	
end0:
	
	ret
