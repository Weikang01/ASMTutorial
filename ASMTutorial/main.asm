.data
myByte db 78
myFloat real4 89.5

.code
SomeFunction proc
	mov al, myByte
	mov ebx, real4 ptr [myFloat]
	ret
SomeFunction endp
end