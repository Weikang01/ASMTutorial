.data

;;;C++ class
;;class MyClass
;;{
;;private:
;;	int i;
;;public:
;;	int GetI()
;;	{
;;		return i;
;;	}
;;};
;;ASM version
;MyClass struct
;	i dd ?
;MyClass ends

;Point struct
;	x dd ?
;	y dd ?
;Point ends
;myPoint Point {0 , 0}

MyUnion union  ; Use "union" instead of "struc(t)"
	small db ?
	medium dw ?
	large dd ?
	huge dq ?
MyUnion ends   ; Note the ENDS!

pp MyUnion { 0ffffffffh }
.code
StructureTest proc
	; accessing structure in data segment
	; mov myPoint.x, 100
	; accessing pointer of a structure
	; mov [rcx].Point.x, 100
	; mov [rcx].MyClass.i, 20

	mov pp.large, 3400537897

	ret
StructureTest endp

end
