bits 64

global	ft_strcmp

section .text

ft_strcmp:
	xor rax, rax			; set rax to 0

.loop:
	mov r8b, [rdi + rax]		; store s1 char as an 8-bit value
	mov r9b, [rsi + rax]		; store s2 char as an 8-bit value
	cmp r8b, r9b			; compare
	jne .end			; if not equal, stop
	cmp r8b, 0
	je .end
	cmp r9b, 0			; if either is 0 ('\0'), stop
	je .end
	inc rax				; increment for loop
	jmp .loop			; repeat

.end:
	movzx rax, r8b			; copy to rax and fill upper bits with 0
	movzx r9, r9b			; copy to r9 and fill upper bits with 0
	sub rax, r9			; equivalent to r8 -= r9 (64-bit)
	ret
