section .text

global _ft_strdup
extern _malloc
extern _ft_strlen ; size_t ft_strlen(const char *s)
extern _ft_strcpy ; char *ft_strcpy(char *dest, const char *src)

_ft_strdup:
	push rdi  ; put const char *s on stack
	call _ft_strlen
	mov rdi, rax
	call _malloc ; rax = (void *)malloc return
	cmp rax, 0
	je exit
	pop rsi ; rsi = const char *s
	mov rdi, rax
	call _ft_strcpy
	jmp exit

exit:
	ret
