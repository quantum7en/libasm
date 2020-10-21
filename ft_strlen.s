section .text

global _ft_strlen ; size_t ft_strlen(const char *s)

_ft_strlen:
	mov	rax, 0	; put 0 to rax
	jmp	count

count:
	cmp BYTE [rdi + rax], 0 ;compare byte at position rdi + rax
	je	exit
	inc rax
	jmp count

exit:
	ret
