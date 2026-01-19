bits	64

global	ft_read
extern	__errno_location

section .text

ft_read:
	mov rax, 0		; sys_read code = 0
	syscall			; call sys_read
	cmp rax, 0		; check sys_read return value
	jl .error		; if < 0, error
	ret

.error:
	neg rax			; negate to obtain positive errno
	push rax		; push errno to stack to save it
	call __errno_location wrt ..plt	; rax = &errno
	pop r8			; pop errno into unused register
	mov [rax], r8	; *rax = errno
	mov rax, -1		; rax = -1
	ret