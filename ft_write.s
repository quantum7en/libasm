section .text

extern ___error

global _ft_write ; rdi = int fd, rsi =const void *buf, rdx = size_t count


_ft_write:
	mov rax, 0x2000004
	syscall ; syscall's return in rax
	jc _err
	ret

_err:
	push rax ; put rax on stack
	call ___error
	pop rdx ; get prev rax in rdx
	mov [rax], rdx
	mov rax, -1
	ret
