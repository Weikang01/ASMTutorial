.code

FlagsFunction proc
	;;Carry flag test
	; mov al, 255
	; add al, 1

	;;Parity flag test
	; mov eax, 3
	; and eax, eax
	; mov eax, 7
	; and eax, eax

	;;Auxiliary Carry flag test
	; mov eax, 15  ; 15+1 in binary is: 00001111 + 1 = 00010000. this "1" in "00010000" is a carry from bit 3 to 4.
	; add eax, 1   ; Lowest 4 bits overflowed!

	;;Zero flag test
	; xor eax, eax  ; ZR = 1
	; add eax, 5    ; ZR = 0
	; cmp eax, ecx

	;;Sign flag test
	; mov eax, 7
	; mov ecx, 12
	; sub eax, ecx  ; PL = 1
	; add eax, ecx  ; PL = 0

	;;Direction flag test
	; std  ; UP=1
	; cld  ; UP=0
	; std  ; UP=1

	;;Overflow flag test
	; mov al, 255  ; al = ff (11111111)  OV = 0
	; shr al, 1    ; al = 7f (01111111)  OV = 1
	; add al, 1    ; al = 80 (10000000)  OV = 1

	;;Change or Read flag registers
	;pushfq
	;pop rax
	;;Change the flags RAX
	;push rax
	;popfq

	ret
FlagsFunction endp
end