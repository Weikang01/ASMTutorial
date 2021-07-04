.data
byte1 db 7
byte2 db 8

.code
SomeFunction proc
	mov rax, 89
	mov cx, ax

	mov byte1, cl
	mov al, byte1
	mov byte2, 19

	lea rax, byte2
	mov byte ptr [rax], 7

	ret
SomeFunction endp
end