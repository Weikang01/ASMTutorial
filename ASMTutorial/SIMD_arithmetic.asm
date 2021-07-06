.data
;;;ESS-126 vectors
;;single-precision
;vec1 real4 1.0, 2.0, 3.0, 4.0
;;dd 0   ;<==  if add this dword segment here, the address of vec2 will no longer be aligned. When we talk about data alignment, we mean is that the address has to be evenly divisible by some number. Since the address is not evenly divisable by 16, vec2 will no longer be aligned for a SSE vector and it may cause access violation.
;;align 16  ; you can add this line to ensure that the next data will be aligned
;;;or use the following C++ functions:
;;;void* _aligned_malloc(size, alignment);
;;;void* aligned_alloc(alignment, size);
;vec2 real4 5.0, 7.0, 1.0, 3.0
;double-precision
;vec1 real8 1.0, 2.0
;vec2 real8 5.0, 7.0

;;;AVX-256 vectors
;;single-precision
;vec1 real4 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0
;vec2 real4 6.0, 4.0, 8.0, 4.0, 5.0, 4.0, 2.0, 9.0
;;double-precision
vec1 real8 1.0, 2.0, 3.0, 4.0
vec2 real8 6.0, 4.0, 8.0, 4.0

.code
SIMDArithmetic proc
	;;;ESS-126 instructions
	;;single-precision instructions
	;movups xmm0, xmmword ptr [vec1]
	;addps xmm0, xmmword ptr [vec2]  ; SSE is a destructive data type, so this instruction will override the elements of the first operand
	;subps xmm0, xmmword ptr [vec2]
	;mulps xmm0, xmmword ptr [vec2]
	;divps xmm0, xmmword ptr [vec2]
	;;double-precision instructions
	;movupd xmm0, xmmword ptr [vec1]
	;addpd xmm0, xmmword ptr [vec2]
	;subpd xmm0, xmmword ptr [vec2]
	;mulpd xmm0, xmmword ptr [vec2]
	;divpd xmm0, xmmword ptr [vec2]

	;;;AVX-256 instructions
	;;single-precision instructions
	;vmovups ymm0, ymmword ptr [vec1]
	;vmovups ymm1, ymmword ptr [vec2]
	;vaddps ymm2, ymm0, ymmword ptr [vec2]  ; Adds the elements from the second and the third operands and stores the result in the first operand. Therefore AVX is called non-destructive instruction set because when we perform an operation, it doesn't necessarily override the inputs
	;vsubps ymm2, ymm0, ymmword ptr [vec2]
	;vmulps ymm2, ymm0, ymmword ptr [vec2]
	;vdivps ymm2, ymm0, ymmword ptr [vec2]
	;;AVX instructions can also work for ESS registers
	;vdivps xmm2, xmm0, xmm1
	;;double-precision instructions
	vmovupd ymm0, ymmword ptr [vec1]
	;vaddpd ymm2, ymm0, ymmword ptr [vec2]
	;vsubpd ymm2, ymm0, ymmword ptr [vec2]
	;vmulpd ymm2, ymm0, ymmword ptr [vec2]
	vdivpd ymm2, ymm0, ymmword ptr [vec2]

	ret
SIMDArithmetic endp


end