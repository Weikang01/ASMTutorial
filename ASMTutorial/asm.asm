.data
myQWordVar sqword 0

.code
; Syntax for instructions :
; AND DEST, SRC
; AND mem/reg, mem/reg/imm
; OR  mem/reg, mem/reg/imm
; NOT mem/reg
; XOR mem/reg, mem/reg/imm

; Truth Table:
; A B  Out
; 0 0  0
; 0 1  0
; 1 0  0
; 1 1  1

TestFunction proc
	mov eax, 100011101010b
	mov ebx, 101000011011b
	mov ecx, 100010101011b
	
	and eax, ecx
	or  eax, ecx

	; equal
	xor eax, ebx
	not eax

	; nor
	or ebx, ebx
	not ebx

	; nand
	and ebx, ebx
	not ebx

	ret
TestFunction endp
end