.data
myFloat real8 45.6

.code
CallingConvention proc
	;; (int/pointer) var1 = RCX
	;; (int/pointer) var2 = RDX
	;; (int/pointer) var3 = R8
	;; (int/pointer) var4 = R9

	;; (float/double) var1 = xmm0
	;; (float/double) var2 = xmm1
	;; (float/double) var3 = xmm2
	;; (float/double) var4 = xmm3

	;; return byte int  -> al
	;; return other int -> rax
	;; return float/double -> xmm0
	;; mov rax(al), result
	;mov rax, rcx
	;mov al, 3
	;movss for single-precision floating point
	;movsd for double-precision floating point
	movsd xmm0, real8 ptr[myFloat]
	ret
CallingConvention endp

end