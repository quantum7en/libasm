section .text
    global _ft_strlen

_ft_strlen:
	mov	rax, 0	; put 0 to rax
	jmp	count

count:
	cmp BYTE [rdi + rax], 0 ;compare byte at position rdi + rax
	je	done
	inc rax
	jmp count

done:
	ret
