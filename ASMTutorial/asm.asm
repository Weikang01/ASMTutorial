.data
myQWordVar sqword 0

.code
AddSubTestFunction proc
	xor rcx, rcx
	mov rax, 2147483648
	add rcx, rax
	mov myQWordVar, rcx
	mov rax, 4
	inc rax
	mov al, 255
	inc al
	mov al, 255
	add al, 1
	mov al, 0
	dec al

	ret
AddSubTestFunction endp
end