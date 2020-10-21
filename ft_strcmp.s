section .text

global _ft_strcmp ; int	ft_strcmp(const char *s1, const char *s2);

_ft_strcmp:
	mov rax, 0
	mov rbx, 0
	mov rcx, 0
	jmp compare

compare:
	mov al, byte [rdi + rcx]
	mov bl, byte [rsi + rcx]
	cmp al, bl
	jne different
	je	equal

different:
	sub rax, rbx
	ret

equal:
	cmp al, 0 ; if '\0'
	je 	exit
	inc rcx
	jmp compare

exit:
	mov rax, 0
	ret
