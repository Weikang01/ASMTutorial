.data
lastFlags dq 0    ; 64 bit copy of flags register

.code
RestoreFlags proc
	push qword ptr [lastFlags]
	popfq
	ret
RestoreFlags endp

SaveFlags proc
	pushfq
	pop qword ptr [lastFlags]
	ret
SaveFlags endp

; int ShiftTest(unsigned long long *rcx)
ShiftTest proc
	mov rdx, qword ptr [rcx]  ; P parameter
	call RestoreFlags  ; Load the last flags

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;
	;; This is the operation we're testing!
	;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	; shl rdx, 1  ; shift left
	; sal rdx, 1  ; shift arithmatic left
	; rol rdx, 1  ; rotate left
	; rcl rdx, 1  ; rotate left throgh the carry flag
	rcl rdx, 1  ; Perform operation

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;
	;; End of operation
	;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	; Set up to return the result in *rcx, and the carry flag in eax
	mov qword ptr [rcx], rdx  ; Move result into * rdx, second param

	mov eax, 0      ; Assume there's no carry
	mov ecx, 1      ; Move 1 into ecx
	cmovc eax, ecx  ; If the carry flag is set, move this 1 into EAX

	call SaveFlags  ; Save flags

	ret
ShiftTest endp

; ShiftDoubleTest(unsigned long long *rcx, unsigned long long *rdx)
ShiftDoubleTest proc
	push rbx  ; Save RBX

	mov rax, qword ptr [rcx]  ; Move param 1 into RAX
	mov rbx, qword ptr [rdx]  ; Move param 2 into RBX

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;
	;; This is the operation we're testing!
	;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	shld rax, rbx, 12  ; Perform operation

	; Place result in *RCX
	mov qword ptr [rcx], rax

	pop rbx  ; Restore caller's RBX
	ret
ShiftDoubleTest endp

end