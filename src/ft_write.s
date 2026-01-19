bits	64

global	ft_write
extern	__errno_location

section .text

ft_write:
	mov rax, 1		; sys_write code = 1
	syscall
	cmp rax, 0
	jl .error		; jump to error if less than 0
	ret
.error:
	neg rax			; negate errno value so that it's positive
	push rax		; push errno value to stack to save it
	call __errno_location wrt ..plt	; rax = &errno
	pop r8			; pop errno value into unused register
	mov [rax], r8	; *rax = errno value
	mov rax, -1		; return -1
	ret