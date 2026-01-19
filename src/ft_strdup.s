bits	64

global	ft_strdup

extern	malloc
extern	ft_strlen
extern	ft_strcpy

section	.text

ft_strdup:
	push rdi		; push string to stack to save it
	call ft_strlen		; get string length
	inc rax			; add 1 for the '\0'
	mov rdi, rax		; copy (length + 1) into rdi
	call malloc wrt ..plt	; call malloc with (length + 1)
	cmp rax, 0
	je .error		; if return val is null, error
	mov rdi, rax		; copy allocated string to rdi
	pop rsi			; pop stack and store the original string in rsi
	call ft_strcpy		; copy into rdi and return
	ret

.error:
	; Malloc sets errno on its own because it's a C function, not a syscall
	pop rdi			; re-balance the stack
	xor rax, rax		; set rax to null
	ret
