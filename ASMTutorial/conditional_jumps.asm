.code
ConditionalJumps proc 

;;;;JO/JNO test
;	mov eax, -9
;	add eax, -12
;	jo Overflowed
;	jno DidntOverflow
;Overflowed:
;	mov rax, 12
;DidntOverflow:
;	mov rax, 15
;	ret

	push rbx

	;;cmovc test
	; mov ebx, 67
	; mov rax, -1
	; clc
	; cmovc eax, ebx ; Move if CY=1

;;;;Loop
;	mov rcx, 10
;LoopHead:
;	; Body of loop!
;	dec rcx
;	jnz LoopHead
	
	;;sete/setne test
	;mov eax, 5
	;mov ecx, 5
	;cmp eax, ecx  ; ZR = 1 if EAX == ECX, 0 if EAX != ECX
	;sete bh  ; set to 1 (if) equal, otherwise 0
	;setne bh ; set to 1 (if) not equal, otherwise 0

	;;jb/ja test
	;;mov rax, 78
	;mov rax, 98
	;mov rbx, 90
	;cmp rax, rbx
	;jb WasBelow
	;ja WasAbove
	;WasBelow:
	;pop rbx
	;ret
	;WasAbove:
	;pop rbx
	;ret

	;;sign flag (smovs) test
	;mov rbx, 100
	;mov rax, 50
	;mov rcx, 90
	;sub rax, rcx    ; rax -= rcx, rax=-40, rax is negative, so it's signed
	;cmovs rax, rbx  ; Move if sign (SF = 1)

	;; parity test
	;setpo al  ; set byte if parity odd
	;setpe bl  ; set byte if parity even

	;;setg(e)/setl(e)
	;mov eax, -9
	;mov ecx, 100
	;cmp eax, ecx
	;setg bl  ; set (if) greater
	;setl bl  ; set (if) less

	pop rbx
	ret


ConditionalJumps endp
end