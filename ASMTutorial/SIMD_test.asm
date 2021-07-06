;// using C++ intrunsics to call SIMD operations
;#include <intrin.h>
;__m256d a = { 0.0, 1.0, 2.0, 3.0 };
;__m256d b = { 2.0, 4.0, 6.0, 8.0 };
;__m256d c;

.data
;my_integer1 dd 0, 1, 2, 3  ; 32-bit int vector
;my_integer2 dd 2, 4, 6, 8
;my_float1 real4 0.0, 1.0, 2.0, 3.0
;my_float2 real4 7.0, 5.0, 3.0, 4.0
my_float1 real8 0.0, 1.0
my_float2 real8 7.0, 5.0

.code
TestSIMD proc
	;;Integer SIMD operations test
	;movdqu xmm0, xmmword ptr [my_integer1] ; MOVDQU xmm, mem: move unaligned double-quadword. Reads 128 bits of integer data into an SSE register. XMMWORD is intended to represent the same type as __m128.
	;movdqu xmm1, xmmword ptr [my_integer2]
	;paddd xmm0, xmm1  ; PADDD xmm, xmm: Packed addition    of DWords. Adds the corresponding 32 bit integers from the first and second operands. Stores results in first operand.
	;psubd xmm0, xmm1  ; PSUBD xmm, xmm: Packed subtraction of DWords. Subs the corresponding 32 bit integers from the first and second operands. Stores results in first operand.

	;;Floating points SIMD operations test
	;movaps xmm0, xmmword ptr [my_float1] ; MOVAPS xmm, mem: move unaligned packed singles. Reads 128 bits or four single precision floating point data into an SSE register.
	;movaps xmm1, xmmword ptr [my_float2]
	movapd xmm0, xmmword ptr [my_float1] ; MOVAPS xmm, mem: move unaligned packed doubles. Reads 128 bits or two double precision floating point data into an SSE register.
	movapd xmm1, xmmword ptr [my_float2]

	;addps xmm0, xmm1  ; ADDPS xmm, xmm: Add      Packed Singles. Adds       the corresponding elements, and stores the results in first operand.
	;subps xmm0, xmm1  ; SUBPS xmm, xmm: Subtract Packed Singles. Subtracts  the corresponding elements, and stores the results in first operand.
	;mulps xmm0, xmm1  ; MULPS xmm, xmm: Multiply Packed Singles. Multiplies the corresponding elements, and stores the results in first operand.
	;divps xmm0, xmm1  ; DIVPS xmm, xmm: Divide   Packed Singles. Divides the corresponding elements, and stores the results in first operand.

	;addpd xmm0, xmm1
	;subpd xmm0, xmm1
	;mulpd xmm0, xmm1
	divpd xmm0, xmm1  ; DIVPD xmm, xmm: Divide Packed Doubles. Divides the corresponding elements, and stores the results in first operand.

	ret
TestSIMD endp

end