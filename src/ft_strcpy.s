bits	64

global	ft_strcpy

section	.text

ft_strcpy:
	xor rax, rax		; set rax to 0

.loop:
	mov r8b, [rsi + rax]	; copy src char as an 8-bit value
	mov [rdi + rax], r8b	; copy into dst at same index
	cmp r8b, 0		; compare with 0
	je .end			; if 0, end of src string
	inc rax			; increment for loop
	jmp .loop		; repeat
.end:
	mov rax, rdi		; copy dst to rax
	ret			; return
