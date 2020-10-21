section .text

extern ___error

global _ft_read ; rdi = int fd, rsi = const void *buf, rdx = size_t count

_ft_read:
	mov rax, 0x2000003
	syscall
	jc _err
	ret

_err:
	push rax
	call ___error
	pop rdx
	mov [rax], rdx
	mov rax, -1
	ret
