section .text
	global _ft_write
	extern ___error

_ft_write:
	test	edi, edi
	js		_err
	mov rax, 0x2000004
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
