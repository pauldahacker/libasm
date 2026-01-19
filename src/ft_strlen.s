bits	64

global	ft_strlen

section	.text

ft_strlen:
	xor rax, rax		; set rax to 0
.loop:
	cmp BYTE [rdi + rax], 0	; byte by byte, compare with 0
	je .end			; if equal to 0, end
	inc rax			; increment for loop
	jmp .loop		; repeat
.end:
	ret			; return accumulator
