.data
.code

Divisions proc
	push rbx

	;; 8 bit DIV reg/mem
	;mov ax, 51
	;mov bl, 10
	;div bl  ; AX -> 0105
	;; Result: AL
	;; Remainder: AH

	;; 16 bit DIV
	;; DX:AX
	;mov ax, 50
	;xor dx, dx
	;mov cx, 3
	;div cx
	;; Result will be in AX  0010 
	;; Remainder will be in DX 0002

	;; 32 bit DIV
	;; EDX:EAX
	;mov eax, 50
	;xor edx, edx
	;mov ecx, 3
	;div ecx
	;; Result will be in EAX  00000010 
	;; Remainder will be in EDX 00000002

	;; 64 bit DIV
	;; RDX:RAX
	;mov rax, 50
	;xor rdx, rdx
	;mov rcx, 3
	;div rcx
	;; Result will be in RAX  00000010 
	;; Remainder will be in RDX 00000002

	pop rbx
	ret
Divisions endp

; Returns the GCD of two unsigned 64 bit integers
;;Euclid algorithm
; C code
; if (x <= 0 || y <= 0)
;	return 0;
; while (y != 0)
; {
;	int tmp = y;
;	y = x % y;
;	x = tmp
; }
; return x;
GCD_ASM proc
	mov rax, 0	; Error value
	cmp rcx, 0  ; compare the 1st number with 0
	jle Finished ; jump to "Finished if rcx == 0
	cmp rdx, 0  ; compare the 2nd number with 0
	jle Finished ; jump to "Finished if rdx == 0

	push rbx
	mov rbx, rdx ; Free RDX so we can use DIV
	LoopHead:
	xor rdx, rdx ; Clear RDX
	mov rax, rcx ; Move Lower 64 bits of dividend into RAX
	div rbx      ; RDX will be the remainder!
	mov rcx, rbx ; Copy X to Y
	mov rbx, rdx ; Copy remainder to X
	cmp rdx, 0
	jne LoopHead

	mov rax, rcx
	pop rbx
	Finished:
	ret
GCD_ASM endp

end