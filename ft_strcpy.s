section .text

global _ft_strcpy ; char *ft_strcpy(char *dest, const char *src)

_ft_strcpy:
	mov	rcx, 0
	mov rbx, 0

copy:
	mov bl, byte [rsi + rcx]
	mov byte [rdi + rcx], bl
	inc rcx
	cmp bl, 0
	je	exit
	jmp copy

exit:
	mov rax, rdi
	ret
