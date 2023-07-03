
bits 32
global _start
extern kernel_early
extern main


_start:
	cli						; clear interrupts
	mov esp, stack			; point the stack pointer to allocate memory
	call kernel_early		; function to be called before main
	call main				; call external main function
	hlt						; halt


stack:
