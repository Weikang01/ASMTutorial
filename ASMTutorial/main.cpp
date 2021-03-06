/*
** Memories
Memories All Read/Write At Different Speeds, And They Have Other Characteristics; Some Are Volatile, Some Are Read-Only Etc.

** Registers
Registers Are Volatile. They Are The Fastest Memory Available To The CPU On The CPU Die Itself. X100 Faster Than RAM, 1000x Faster Than Hard Drives.

The CPU Reads Data From Other Memories, Performs Calculations In Its Registers, And Writes The Results Back To The Other Memory. The Other Memory Areas Basically Only Allow Reading And Writing. All Computation Is Performed With Registers.

8086 Registers

The 8086 hit the world in 1978 and was incredibly popular. It was a 16 bit processor, which means most of its general purpose registers are 16 bits, and most of its instructions operate on 16 bits.

** General Purpose Registers (GPR)
* 16 bits : AX    BX    CX    DX
*  8 bits : AH/AL BH/BL CH/CL DH/DL
AX/DX : Used For Arithmetic Operations Like Division, etc.
CX : Used For Index In A Loop

** Index Registers
* 16 bits : SI DI BP SP
SI : Source Index
DI : Destination Index
BP : Base Pointer
SP : Stack Pointer

** Instruction Pointer (Program Counter)
* 16 bits : IP
IP : Point In RAM Where The Instruction Are Being Read From

** Segment Registers
* 16 bits : CS DS ES SS
Segment Registers Are Used By The Operating System For Various Incidental Things, Like Paging Information and Threading Information.

** Flags Register
* 16 bits : Flags
Stores The Stats Of Comparisons And Other Instructions So We Can Act On That Stat.
*/
/*
32 bit 80386

For Backwards Compatibility, All Of The 8086's Original 16 Bit Registers Were Maintained. But Most Registers Also Got A 32 Bit Version; 32 Bit Versions Have The Same Names As The Original But They Begin With "E".
** General Purpose:
* 32 bits : EAX   EBX   ECX   EDX
* 16 bits : AX    BX    CX    DX
*  8 bits : AH/AL BH/BL CH/CL DH/DL

** Index Regs:
* 32 bits : ESI EDI EBP ESP
* 16 bits : SI  DI  BP  SP

The IP And Flags Register Also Got 32 Bit Versions, But The Segment Registers Remained As 16 Bits. Instead Of Increasing The Size Of The Segment Registers, They Added Two New Ones, FS And GS.

** IP And Flags:
* 32 bits : EIP eFlags
* 16 bits : IP  Flags

** Segment Registers
* 16 bits : CS DS ES SS FS GS

*/
/*
Pentium !V And x64

** General Purpose:
* 64 bits : RAX   RBX   RCX   RDX
* 32 bits : EAX   EBX   ECX   EDX
* 16 bits : AX    BX    CX    DX
*  8 bits : AH/AL BH/BL CH/CL DH/DL

** Index Regs:
* 64 bits : RSI RDI RSP RBP 
* 32 bits : ESI EDI ESP EBP 
* 16 bits : SI  DI  SP  BP  

** IP:
* 64 bits : RIP
* 32 bits : EIP
* 32 bits : IP

** "R" Registers ("D" - "Double", "W" - "Word", "B" - "Byte")
* 64 bits : R8  R9  R10  R11  R12  R13  R14  R15
* 32 bits : R8D R9D R10D R11D R12D R13D R14D R15D
* 16 bits : R8W R9W R10W R11W R12W R13W R14W R15W
*  8 bits : R8B R9B R10B R11B R12B R13B R14B R15B

** Flags:
* 64 bits : rFlags
* 32 bits : eFlags
* 32 bits : Flags

Tips : There's something to be aware of when using 32 bit registers in 64 bit mode. Firstly, it is not wrong, nor frowned upon to use 32 bit instructions, it is perfectly normal and very common, but they have an unintuitive and strange side effect:
	* Using instructions with 32 bit registers Zeros the top of the 64 bit registers! That's only 32 bit operations, 8 bit and 16 bit do not.
This happens with the old regs like EAX, EDX etc. and the ones too! As far as I can tell, there's no good reason other than Intel/AMD decided that's what would happen!

*/
/*
Fundamental Data Types
There's only a handful of fundamental data types. Most Assemblers allow us to construct our own data types from these using struct, but the CPU itself only really knows a few integer data types and a few floating point.
In this vid, we'll look at the x64 data types, and at the end we'll define some variables using them.

* Integer:
* byte, word, dword, qword

* Floating Point:
* real4, real8, real10

* SIMD Pointers
* xmmword, ymmword, zmmword
* Note : ZMMWORD is for AVX512

Integers Signed vs Unsigned
ASM is not type safe. Signed vs. Unsigned comes down to which instructions you use.
For some operations (e.g. DIV and MUL), there are separate instructions for signed and unsigned.
For other operations (e.g. ADD and SUB), the resulting bits are identical so there's only one instruction provided.
It is up to the programmer to select the appropriate instructions.

Two's Complement
x86 is designed to use Two's Complement when performing signed integer arithmetic.
In this system, the most significant bit (the left-most bit) is the sign bit. A number is positive if the sign bit is 0, and negative if the sign bit is 1.
If the sign bit is 1, then the value being represented is negative the logical complement of the pattern incremented. See Wikipedia "Two's complement" for more info. (https://en.wikipedia.org/wiki/Two%27s_complement)

Integer Data Type Ranges
* Byte : 8 bits wide, ranges from 0 to 255 when unsigned and from -2^7 to 2^7-1 when signed.
* Word : 16 bits, ranges from 0 to 65,535 when signed and from -2^15 to 2^15-1 when signed.
* Dword (Double-Word) : 32 bits, ranges from 0 to 2^32 when signed and from -2^31 to 2^31-1 when signed.
* Qword (Double-Quad-Word) : 64 bits, ranges from 0 to 2^64 when signed and from -2^63 to 2^63-1 when signed.

Floating Point Data Types
* real4 : IEEE754 single precision float. 32 bits wide; 1 sign bit, 8 bit exponent, 23 bit mantissa.
* real8 : IEEE754 single precision float. 32 bits wide; 1 sign bit, 11 bit exponent, 53 bit mantissa.
* real10 : IEEE754 extended precision float. 80 bits wide; 1 sign bit, 15 bit exponent, 64 bit mantissa.
Note : real10 is only used with the x87 FPU, it is largely ignored nowadays, but offers amazing precision!

SIMD Data Types
These are used for SIMD packed data.
* xmmword: 128 bits, 16 bytes, 8 words, 4 dwords or 2 qwords.
* ymmword: 256 bits, 32 bytes, 16 words, 8 dwords or 4 qwords.
** zmmword: 512 bits, 64 bytes, 32 words, 16 dwords or 8 qwords.

Summary
____________________________________________________________
Name              |Type |Bits|Bytes|Pointer    |Defining   |
Byte              |Int  |8   |1    |byte ptr   |db or byte |
Word              |Int  |16  |2    |word ptr   |dw or word |
Double Word       |Int  |32  |4    |dword ptr  |dd or dword|
Quad Word         |Int  |64  |8    |qword ptr  |dq or qword|
IEEE 754 Single   |Float|32  |4    |real4 ptr  |real4      |
IEEE 754 Double   |Float|64  |8    |real8 ptr  |real8      |
IEEE 754 Extended |Float|80  |10   |real10 ptr |real10     |
MMX Packed 64bit  |SIMD |64  |8    |qword ptr  |dq or qword|
SSE Packed 128bit |SIMD |128 |16   |xmmword ptr|xmmword    |
AVX Packed 256bit |SIMD |256 |32   |ymmword ptr|ymmword    |
AVX512 Pckd 512bit|SIMD |512 |64   |???        |???        |
____________________________________________________________
Note : There are more. e.g. mmword is identical to qword, except you cannot define any initial data when defining. It's meant for the MMX SIMD instruction set. All of these terms are Assembler specific, the above table shows the syntax for Microsoft's MASM.

*/
/*
MOV and LEA, two related instruction

* Move : MOV
The most fundamental movement instruction is MOV. It takes two operands of the same size, and moves the data (copies it) from the source operand to the destination.
				MOV dest, src
Mote : MOV does not change the Flags register. If both operands are the same register, it acts as a NOP :
				MOV AL, AL or MOV EAX, EAX = 2 byte NOP
				MOV AX, AX or MOV RAX, RAX = 3 byte NOP

* Load Effective Address : LEA
The LEA instruction loads an address. If you have some variable, you can load the address of it into a register and manipulate the data indirectly with the register as a pointer. LEA does not change any flags.
				LEA dst, src
Note : LEA is actually an arithmetic instruction, it computes an SIB address.

*/
/*
ADD, SUB INC and dec

Addition and Subtraction
There are some interesting things about many instructions of the instructions in x86, and these are no exception. On the surface, they Add, Subtract, Increment and Decrement, but under the hood, they're weird little monsters, just like most of the x86 instructions, and they do some pretty strange things!

* ADD
				ADD reg/mem, reg/mem/imm
The add instruction adds the source to the destination and stores in the destination. It is used for both signed and unsigned arithmetic, depending on how the flags are read.
The Overflow flag indicates a signed carry. The Carry flag indicates unsigned carry.
Flags : Overflow, Carry, Sign, Zero, Auxiliary Carry, Parity
LOCK is supported

* Tricks and Traps
Using the original registers, EAX, CX, BL etc. generates more efficient machine code than using the new ones, R8B, R12W etc. New registers, and 64 bit instructions add a REX prefix in machine code.
Use "ADD reg, 0" to update the flags according to reg without changing it, similar to "AND reg, reg" and "OR reg, reg". These are slightly different to "CMP reg, reg" since CMP sets the flags as "SUB reg, reg".
Use "ADD reg, 1" if you need to "INC reg" which affects the carry flag.
ADD is faster than the multiplication instructions, so to double a reg, you can use for example "ADD ax, ax". It is more common to use shifts for this purpose.

Sign Extension
ADD sign extends an immediate operand when the operands are not of the same size. This only matters when the destination is 64 bits, but there is no "ADD reg64, imm64"!
When the destination is 64 bits, the immediate is always read as 32 bits. It will be sign extended, so if the 32st bit is a 1, you'll get a negative result!
				ADD RCX, 2147483648; add rcx, ffffffff8000000h
If you need to add a 64 bit immediate to a reg or mem, you have to use an intermediate MOV instruction:
MOV rax, 2147483648
ADD rcx, rax

* SUB
				SUB reg/mem, reg/mem/imm
SUB subtracts the second operand from the first, and stores the result in the first.
The Overflow flag indicates a signed borrow. The Carry flag indicates unsigned borrow.
Flags : Overflow, Carry, Sign, Xero, Auxiliary Carry, Parity
LOCK is supported

* Tricks
64 bit SUB is similar to ADD in the way it sign extends a 32 bit immediate. If you need to subtract a 64 bit immediate, you have to use a MOV first!
A quick way to Zero is "SUB reg, reg". "XOR reg, reg" is more common for this purpose.
Use "SUB x, 1" to achieve a "DEC x" which affects the carry flag.
You can use ADD and SUB to perform a swap, similar to XOR swap, but XCHG instruction is faster and easier to read.

* INC
The INC instruction, short for Increment, adds 1 to the destination.
				INC reg/mem
Flags: Does not affect Carry! Overflow, Sign, Xero, Auxiliary and Parity
LOCK is supported

* INC and Carry Flag
The INC and DEC instructions does not change the carry flag. I believe this has to do with the "LOOP" instruction. So if you need to check the carry flag after an INC, you should use "ADD x, 1" instead.
Most of the time, "INC reg" is the same speed as "ADD reg, 1", but for 32 and 64 bit regs, "INC" is smaller (3 bytes vs 4), and in rare occasions where you need a loop's body fit into some specific number of bytes, INC might be the best choice.

* DEC
The DEC, short for Decrement, instruction subtracts 1 from the destination.
				DEC reg/mem
The DEC instruction does not change the carry flag! same as INC, Use "SUB x, 1" to affect the carry.
Flags: Overflow, Sign, Xero, Auxiliary and Parity


..................................................................
*/
/*
Shift, Rotate and Bit Manipulation Instructions
Exploring x64 shift and rotate instructions

Shift instructions move the bits in the egisters or RAM as throgh they are bit strings, written from left to right with the most significant bit on the left. Rotations are similar to shifts, only the bits re-enter on the opposite side as they leave.

* Instructions:
SHL/SAL, SHR, SAR, ROR, ROL, RCR, RCL, SHRD, SHLD
SHL and SAL are the same thing (lead to identital machine code), assemblers allow two mnemonics, but there is only one instruction.
_________________________
Instruction |Machine Code|
SHL EAX, 1  |D1 E0       |
SAL EAX, 1  |D1 E0       |
_________________________

Second: Speeds
Execution Speed Tests:
____________________________________________________________
Instruction|Type       |Description        |Speed           |
SHL/SHR/SAR|reg, imm   |Shift              |Fast (316)      |
SHL/SHR    |reg, CL    |Shift              |Moderate (601)  |
SHL/SHR/SAR|mem, imm   |Shift              |Slow (1622)     |
SHL/SHR/SAR|reg, CL    |Shift              |Slow (1500)     |
           |           |                   |                |
ROL/ROR    |reg, imm   |Rotate             |Fast (316)      |
ROL/ROR    |reg, 1     |Rotate             |Moderate (514)  |
ROL/ROR    |reg, CL    |Rotate             |Moderate (601)  |
ROL/ROR    |mem, imm   |Rotate             |Slow (1470)     |
ROL/ROR    |mem, CL    |Rotate             |Slow (1504)     |
		   |           |                   |                |
RCR/RCL    |reg, imm   |Rot through Carry  |Moderate (601)  |
RCR/RCL    |reg, CL    |Rot through Carry  |Moderate (601)  |
RCR/RCL    |mem, imm   |Rot through Carry  |Slow (1513)     |
RCR/RCL    |mem, CL    |Rot through Carry  |Very Slow (2404)|
		   |           |                   |                |
SHLD/SHRD  |reg,reg,imm|Dbl Precision Shift|Moderate (889)  |
SHLD/SHRD  |reg,reg,CL |Dbl Precision Shift|Moderate (889)  |
SHLD/SHRD  |mem,reg,imm|Dbl Precision Shift|Very Slow (2128)|
____________________________________________________________
*/
/*
Flags Register
_______________________________________________
15|14|13 12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0| 
  |NT|IOPL |OF|DF|IF|TF|SF|ZF|  |AF|  |PF|  |CF|
Only 0 to 15 are represented here. The rest are reserved and/or system flags.

* 0: CF
Carry Flag : Represents an unsigned overflow.
Called CY in visual studio

(Note : -1 always has all the bits to 1! Signed -1 has the same bit pattern as the largest unsigned value :
111111...11111)

* 2: PF
Parity Flag :
PE in visual studio!

1 last result had even parity.
0 last result had odd parity.

Was for checking integrity of serial data.

Example : You read 8 bits from ASCII file: 00110101
You know that only the low 7 bits are meant to represent the character.
0 0110101
The extra first bit is an error checking bit! It is the Parity!!
Parity 0 means Odd! There should be an odd number 1's:
0 0"11"0"1"0"1"
There are 4. 4 is Even, so the Parity bit is telling us that the data is corrupt!!

* 4: AF
Auxiliary Carry:
AC in visual studio
Overflow or carry of the lowest nibble (lowest 4 bits).

Used for Binary Code Decimal BCD. Not applicable in x64!

* 6: ZF
Zero Flag!!!
ZR in visual studio
Was previous result 0?
if Yes: ZR = 1
if No : ZR = 0
Also means Equals!!

* 7: SF
Sign Flag
PL in Visual Studio.
1 if last result was Negative
0 if last result was Positive

* 10: DF
Direction Flag:
UP in Visual studio.
0 Reading strings forwards
1 Reading strings backwards

* 11: OF
Overflow Flag:
OV in visual studio
Represents a Sign over flow.
Did the Sign change?
Overflow on the 2nd from left bit!

* 8: TF
Trap Flag: Allows debuggers to step throgh code
* 9: IF
Interrupt Flag: Allows interrupts to be called
* 12,13: IOPL
Shows IO port privilege level
* 14: NT
Nested Task: Shows if the task is nested

CPUID: If you can toggle bit 21, then the CPU is capable of the CPUID instruction.
*/
/*
Alignment:
.data ; Data will be naturally aligned to 64 byte cache line!
alignedQWord1 dq 0
alignedQWord2 dq 0
alignedQWord3 dq 0
dontDoThis			db 0
unalignedQWord		dq 0  ; 1 byte is from the next cache line!

Accessing data that spans multiple cache lines is almost never a good idea! Setting up your data as above will cause the unalignedQWord to span two cache lines (cache lines are 64 byte on most current hardware). This results in two requests from RAM every time we read/write. This means a substantial performace hit! 2644 vs 1500 for SHL, 2700 vs 2100 for SHLD tests. Only instruction where it did not seem to make a lot of difference is RCL/RCR, persumably because the instruction is unaligned read/write is occurring?
SAR, when used as integer division rounds towards -Infinity. So -25/2 gives
*/
/*
* Conditional Jumps
Jcc rel8/16/32
If the condition "cc" is true, then the IP will jump to the position specified by the relative offset. Otherwise, IP will fall through to next instruction.
In practice, we supply a label, and the Assembler converts it to the RIP relative address

* Conditional Moves
CMOVcc reg, reg/mem
If "cc" is true, the value of the second operand is moved into the first. Otherwise, the first is unchanged.
There are no 8 bit versions of these instructions.
The 32 bit versions will Zero the upper32
the 64 bit destination regardless of the condition

* Set Byte
SETcc reg/mem8
If "cc" is true, the value 1 is moved into the operand. Otherwise, the value 0 is moved.
Only 8 bit operands are allowed.

cc Condition Codes
_____________________________________________________________
JO: Overflow                     |JS: Sign                   |
JNO: Not Overflow                |JNS: NOT Sign              |
JB/JC/JNAE: Carry Unsigned       |JP/JPE: Parity Even        |
JE/JZ: Zero                      |JL/JNGE: Less Signed       |
JNE/JNZ: Not Zero                |JNL/JGE: Not Less Signed   |
JBE/JNA: Below or Equal Unsigned |JLE/JNG: Not Greater Signed|
JNBE/JA: Above Unsignd           |JNLE/JG: Greater SIgned    |
(We can use CMOV, or SET in place of the "J" when using Conditional moves and set byte. The "J" is for Jump.)
*/
/*
Parameter Passing
* Windows "C" Calling Convention
_________________________________________
    |Int  |Float/Double|Pointer/Obj/Array|
1st |RCX  |XMM0		   |RCX				 |
2nd |RDX  |XMM1		   |RDX				 |
3rd |R8	  |XMM2		   |R8				 |
4th |R9	  |XMM3		   |R9				 |
more|Stack|Stack	   |Stack			 |
Integer and pointer returns are in RAX.
Floating point returns are in XMM0
*/
/*
ASM Structures
Many Assemblers include structure functionality to organise code. This part, we'll look at MASM structures and how they can be made to interact with C++ structures.

* Declaration Syntax

<Structure's Name> struct
	<member variable name> <datatype> <value or ?>
	<member variable name> <datatype> <value or ?>
<Structure's Name> ends

Note: Question marks means we don't care what these initialise to!
example:
Point struct
	x dd ?
	y dd ?
Point ends

* Define a structure
<variable name> <Structure's Name> {var1, var2...}
Note: Triangle braces, <var1, var2...> is the same!

example:
myPoint Point { 0, 0 }
or
myPoint Point < 0, 0 >

* Accessing Members
example:
myPoint declared in data segment 
			mov myPoint.x, 100

If RCX is a pointer to Point
			mov [rcx].Point.x, 90

* C++ Natural Alignment
By default many C++ compilers align data so the offsets within the structures are divisible by the data size.

struct MyStruct
{
	char c;  // Offset 0
	int i;   // Offset 4
	short s; // Offset 8
	double d;// Offset 16
};           // Total: 24 bytes!
_______________________________________________
c| | | |i|i|i|i|s|s| | | | | | |d|d|d|d|d|d|d|d|

Example: change the order of members to get different size
	struct MyStruct
	{
		char c;  // Offset 0
		double d;// Offset 8
		char q;  // Offset 16
		double v;// Offset 24
	};           // Total: 32 bytes!
	
	struct MyStruct
	{
		char c;  // Offset 0
		char q;  // Offset 1
		double d;// Offset 8
		double v;// Offset 16
	};           // Total: 24 bytes!

* ASM Version
In ASM we have to add the padding ourselves!
MyStruct struct
	c db ?
		db 3 dup(0)    ; Padding!
	i dd ?
	s dw ?
		db 4 dup(0)    ; Padding!
	d real8 ?
MyStruct ends

* #pragma pack the C++
Using packing, C++ will pack data the same as ASM!

#pragma pack(1)  // align your data to addresses divisable by 1, in other words, any address. It means to pack the data as tight as possible
struct MyStruct
{
	char c;  // Offset 0
	int i;   // Offset 1
	short s; // Offset 5
	double d;// Offset 7
};           // Total: 15 bytes!
_____________________________
c|i|i|i|i|s|s|d|d|d|d|d|d|d|d|

ASM Version of this fully-packed structure
MyStruct struct
	c db ?
	i dd ?
	s dw ?
	d real8 ?
MyStruct ends

* C++ Classes are the same!
Using packing, C++ will pack data the same as ASM!

class MyClass
{
private:  // ASM doesn't care if these are private!
	char c;
	int i;
	short s;
	double d;
	void Method();  // Methods do not take up any space!
};

* More on ASM Structs
We can supply default values
Point struct
	x dd 100  ; Default value
	y dd 100  ; Default value
Point ends

point1 Point {}      ; Use defaults
point2 Point {, 99}  ; x:100, y:99
point3 Point {0, 0}  ; Override both defaults


* Unions
Unions are also Available! Elements overwrite each other. C++ and ASM packing is the same.

union MyUnion
{
	char small;
	short medium;
	int large;
	long long huge;
};

MyUnion union  ; Use "union" instead of "struc(t)"
	small db ?
	medium dw ?
	large dd ?
	huge dq ?
MyUnion ends   ; Note the ENDS!

* Defining and Accessing Unions
Defining and accessing union members is the same as structures

pp MyUnion { 0ffffffffh }  ; Only the low 8 bits, first member will be set!
.code
SomeFunction proc
	mov pp.medium, 90
	mov [rcx].MyUnion.large, 3400537897
SomeFunction endp

* Nested Structures
You can nest structures too!

Point struct
	x real4 ?
	y real4 ?
Point ends

Line struct
	startPoint Point {0.0, 0.0}  ; Initialisers for nested
	finishPoint Point { }
Line ends

line1 Line { }  ; Use defaults
line2 Line { \  ; Slashes required for multiple lines!
	{100.0, 89.0}, \
	(25.0, 78.0} \
}
*/
/*
* Introduction to SIMD

- Flynn's Taxonomy splits computing architecture into four different general types:
- SISD : Single Instruction Single Data == Regular Scalar Programming.
- SIMD : Single Instruction Multiple Data : One instruction but it's executed on lots of different data elements at once
- MISD : Multiple Instruction Single Data, sometime be used for debugging purposes.
- MIMD : Multiple Instruction Multiple Data. Ex: Modern Multi-core CPU

Scalar Addition: A + B = C
SIMD Addition:
A0 + B0 = C0
A1 + B1 = C1
A2 + B2 = C2
A3 + B3 = C3

* SIMD Instruction Sets
* SSE, AVX, AVX512 and MMX

* x64 Assembly and SIMD
SSE
Streaming SIMD Instructions
SSE came out with whole bunch of generations
- SSE 1 was designed for single-precision floating point arithmetic
- SSE 2 was designed for double-precision floating point as well as integer
- SSE 3 came out in two generations.
	- 1st gen SSE 3. Offered few horizontal operations
	- 2nd gen SSE 3. The extension of the previous, added more horizontal operations.
- SSE 4 contains multiple generations as well.
	- SSS 4.1, 4.2, 4a. Offered various string operations, blend operations, etc.
- AVX offers operations on single precision and double precision floats, the vector size was double to 256 bits.
- AVX 2 added the integer operations to the AVX instruction sets.
- AVX 512 doubles the size of the vector to 512 bits, and the instructions involved in AVX 512 various.
- MMX is the first SIMD instruction set that x86 CPUs got, way back with the Pentium MMX in 1997. The instruction set is largely considered obsolete nowadays.


* MMX came out back in 1999 with 8 registers: from MM0 to MM7.
* SSE came out and doubled the register count: from XMM0 to XMM15. This is only in 64-bit mode.
* AVX has 16 registers: from YMM0 to YMM15
* AVX12 increased their register count to 32: from ZMM0 to ZMM31. If you are programming for an AVX-512 capable CPU you'll get 32 SSE registers as well.
All of these registers are aliased to each other so except for MMX these registers are actually aliased to each other. So the low half of the AVX registers is actually the 128-bit SSE registers and likewise the low half of the AVX-512 is the 256 bit AVX registers.

* SIMD Data Types: From Scalar Bytes to 512 bit Vectors

- Start with a recap of the basic data types:
(8  bits)   byte                           :0xff
(16 bits)   word                           :0xffff
(32 bits)   dword                          :0xffffffff
(64 bits)   qword                          :0xffffffffffffffff
(32 bits)   single-precision floating point: 0.0f
(64 bits)   double-precision floating point: 0.0

(128 bits vector) SSE can be split up in lots of different ways.
                          bytes : 16 operations at once
                          words :  8 operations at once
                         dwords :  4 operations at once
                         qwords :  2 operations at once
single-precision floating point :  4 operations at once
double-precision floating point :  2 operations at once

(256 bits vector) AVX
						  bytes : 32 operations at once
						  words : 16 operations at once
						 dwords :  8 operations at once
						 qwords :  4 operations at once
single-precision floating point :  8 operations at once
double-precision floating point :  4 operations at once

(512 bits vector) AVX512
						  bytes : 64 operations at once
						  words : 32 operations at once
						 dwords : 16 operations at once
						 qwords :  8 operations at once
single-precision floating point : 16 operations at once
double-precision floating point :  8 operations at once

*/
/*
* SIMD Floating-Point Arithmetic
- ADD, SUB, MUL, DIV for Floats and Doubles

Recap:
- SSE Registers has vectors of 128-bits wide, so there are 16 different registers ( in 32-bit mode, there are only 8 SSE registers) from XMM0 to XMM15.

- AVX : Advanced Vector Extension: 256-bits wide, registers are called from YMM0 up to YMM15. It is important to keep in mind that the low 128 bits of the AVX registers is actually the SSE registers.

- CPUID is an instruction which determines the hardware capabilities at runtime. It's usually safer to check the hardware with a CPUID call!

*/
/*
*/

#include <iostream>
#include <intrin.h>

extern "C" int SIMDArithmetic();

void PrintBits(int carry, unsigned long long p, int bitCount)
{
	std::cout << "C: " << carry << " ";
	for (int j = bitCount - 1; j >= 0; j--)
	{
		std::cout << ((p >> j) & 1);
	}
	std::cout << std::endl;
}

#ifdef _WIN32

//  Windows
#define cpuid(info, x)    __cpuidex(info, x, 0)

#else

//  GCC Intrinsics
#include <cpuid.h>
void cpuid(int info[4], int InfoType) {
	__cpuid_count(InfoType, 0, info[0], info[1], info[2], info[3]);
}

#endif

void CheckCPUSupport()
{
	//  Misc.
	bool HW_MMX        ;
	bool HW_x64        ;
	bool HW_ABM        ;      // Advanced Bit Manipulation
	bool HW_RDRAND     ;
	bool HW_BMI1       ;
	bool HW_BMI2       ;
	bool HW_ADX        ;
	bool HW_PREFETCHWT1;

	//  SIMD: 128-bit
	bool HW_SSE  ;
	bool HW_SSE2 ;
	bool HW_SSE3 ;
	bool HW_SSSE3;
	bool HW_SSE41;
	bool HW_SSE42;
	bool HW_SSE4a;
	bool HW_AES  ;
	bool HW_SHA  ;

	//  SIMD: 256-bit
	bool HW_AVX ;
	bool HW_XOP ;
	bool HW_FMA3;
	bool HW_FMA4;
	bool HW_AVX2;

	//  SIMD: 512-bit
	bool HW_AVX512F   ;    //  AVX512 Foundation
	bool HW_AVX512CD  ;   //  AVX512 Conflict Detection
	bool HW_AVX512PF  ;   //  AVX512 Prefetch
	bool HW_AVX512ER  ;   //  AVX512 Exponential + Reciprocal
	bool HW_AVX512VL  ;   //  AVX512 Vector Length Extensions
	bool HW_AVX512BW  ;   //  AVX512 Byte + Word
	bool HW_AVX512DQ  ;   //  AVX512 Doubleword + Quadword
	bool HW_AVX512IFMA; //  AVX512 Integer 52-bit Fused Multiply-Add
	bool HW_AVX512VBMI; //  AVX512 Vector Byte Manipulation Instructions

	int info[4];
	cpuid(info, 0);
	int nIds = info[0];

	cpuid(info, 0x80000000);
	unsigned nExIds = info[0];

	//  Detect Features
	if (nIds >= 0x00000001) {
		cpuid(info, 0x00000001);
		HW_MMX = (info[3] & ((int)1 << 23)) != 0;
		HW_SSE = (info[3] & ((int)1 << 25)) != 0;
		HW_SSE2 = (info[3] & ((int)1 << 26)) != 0;
		HW_SSE3 = (info[2] & ((int)1 << 0)) != 0;

		HW_SSSE3 = (info[2] & ((int)1 << 9)) != 0;
		HW_SSE41 = (info[2] & ((int)1 << 19)) != 0;
		HW_SSE42 = (info[2] & ((int)1 << 20)) != 0;
		HW_AES = (info[2] & ((int)1 << 25)) != 0;

		HW_AVX = (info[2] & ((int)1 << 28)) != 0;
		HW_FMA3 = (info[2] & ((int)1 << 12)) != 0;

		HW_RDRAND = (info[2] & ((int)1 << 30)) != 0;
	}
	if (nIds >= 0x00000007) {
		cpuid(info, 0x00000007);
		HW_AVX2 = (info[1] & ((int)1 << 5)) != 0;

		HW_BMI1 = (info[1] & ((int)1 << 3)) != 0;
		HW_BMI2 = (info[1] & ((int)1 << 8)) != 0;
		HW_ADX = (info[1] & ((int)1 << 19)) != 0;
		HW_SHA = (info[1] & ((int)1 << 29)) != 0;
		HW_PREFETCHWT1 = (info[2] & ((int)1 << 0)) != 0;

		HW_AVX512F = (info[1] & ((int)1 << 16)) != 0;
		HW_AVX512CD = (info[1] & ((int)1 << 28)) != 0;
		HW_AVX512PF = (info[1] & ((int)1 << 26)) != 0;
		HW_AVX512ER = (info[1] & ((int)1 << 27)) != 0;
		HW_AVX512VL = (info[1] & ((int)1 << 31)) != 0;
		HW_AVX512BW = (info[1] & ((int)1 << 30)) != 0;
		HW_AVX512DQ = (info[1] & ((int)1 << 17)) != 0;
		HW_AVX512IFMA = (info[1] & ((int)1 << 21)) != 0;
		HW_AVX512VBMI = (info[2] & ((int)1 << 1)) != 0;
	}
	if (nExIds >= 0x80000001) {
		cpuid(info, 0x80000001);
		HW_x64 = (info[3] & ((int)1 << 29)) != 0;
		HW_ABM = (info[2] & ((int)1 << 5)) != 0;
		HW_SSE4a = (info[2] & ((int)1 << 6)) != 0;
		HW_FMA4 = (info[2] & ((int)1 << 16)) != 0;
		HW_XOP = (info[2] & ((int)1 << 11)) != 0;
	}

#define PrintSupportItem(x) std::cout << #x << ": " << x << std::endl
	std::cout << "Misc." << std::endl;
	PrintSupportItem(HW_MMX        );
	PrintSupportItem(HW_x64        );
	PrintSupportItem(HW_ABM        );
	PrintSupportItem(HW_RDRAND     );
	PrintSupportItem(HW_BMI1       );
	PrintSupportItem(HW_BMI2       );
	PrintSupportItem(HW_ADX        );
	PrintSupportItem(HW_PREFETCHWT1);
	std::cout << "SIMD: 128-bit" << std::endl;
	PrintSupportItem(HW_SSE  );
	PrintSupportItem(HW_SSE2 );
	PrintSupportItem(HW_SSE3 );
	PrintSupportItem(HW_SSSE3);
	PrintSupportItem(HW_SSE41);
	PrintSupportItem(HW_SSE42);
	PrintSupportItem(HW_SSE4a);
	PrintSupportItem(HW_AES  );
	PrintSupportItem(HW_SHA  );
	std::cout << "SIMD: 256-bit" << std::endl;
	PrintSupportItem(HW_AVX );
	PrintSupportItem(HW_XOP );
	PrintSupportItem(HW_FMA3);
	PrintSupportItem(HW_FMA4);
	PrintSupportItem(HW_AVX2);
	std::cout << "SIMD: 512-bit" << std::endl;
	PrintSupportItem(HW_AVX512F   );
	PrintSupportItem(HW_AVX512CD  );
	PrintSupportItem(HW_AVX512PF  );
	PrintSupportItem(HW_AVX512ER  );
	PrintSupportItem(HW_AVX512VL  );
	PrintSupportItem(HW_AVX512BW  );
	PrintSupportItem(HW_AVX512DQ  );
	PrintSupportItem(HW_AVX512IFMA);
	PrintSupportItem(HW_AVX512VBMI);
}

int main()
{
	CheckCPUSupport();

	SIMDArithmetic();

	// using C++ intrunsics to call SIMD operations
	// Single-precition SSE
	__m256d a = { 0.0, 1.0, 2.0, 3.0 };
	__m256d b = { 2.0, 4.0, 6.0, 8.0 };
	__m256d c;

	c = _mm256_add_pd(a, b);

	__m128 v1 = { 1,2,3,4 }; // Define a vector
	__m128 v2 = { 5,6,7,8 }; // Define another
	//__m128 v3 = _mm_add_ps(v1, v2);  // Add them together using ADDPS
	//__m128 v3 = _mm_sub_ps(v1, v2);  // Sub the first by the second using SUBPS
	//__m128 v3 = _mm_mul_ps(v1, v2);  // Mult them together using MULPS
	__m128 v3 = _mm_div_ps(v1, v2);  // Div the first by the second using DIVPS
	float f[4];
	// Store the results in an array:
	_mm_storer_ps(f, v3);  // Unaligned, f need not be aligned

	// Print the results
	std::cout << "Value: " << f[0] << std::endl;
	std::cout << "Value: " << f[1] << std::endl;
	std::cout << "Value: " << f[2] << std::endl;
	std::cout << "Value: " << f[3] << std::endl;

	// Double-precition SSE
	__m128d v1d = { 1.0,2.0 }; // double-precision vector, we can store 2 doubles, since each of them is 64 bits
	__m128d v2d = { 3.0,4.0 };
	//__m128d v3d = _mm_add_pd(v1d, v2d);
	//__m128d v3d = _mm_sub_pd(v1d, v2d);
	//__m128d v3d = _mm_mul_pd(v1d, v2d);
	__m128d v3d = _mm_div_pd(v1d, v2d);

	// AVX
	// Single-precition AVX
	__m256 avx1 = { 1,2,3,4,5,6,7,8 };  // 256 bit of width can store 8 integers
	__m256 avx2 = { 9,1,2,3,4,5,6,7 };
	//__m256 avx3 = _mm256_add_ps(avx1, avx2);
	//__m256 avx3 = _mm256_sub_ps(avx1, avx2);
	//__m256 avx3 = _mm256_mul_ps(avx1, avx2);
	__m256 avx3 = _mm256_div_ps(avx1, avx2);

	// Double-precition AVX
	__m256d avx1d = { 1,2,3,4 };
	__m256d avx2d = { 9,1,2,3 };
	//__m256d avx3d = _mm256_add_pd(avx1d, avx2d);
	//__m256d avx3d = _mm256_sub_pd(avx1d, avx2d);
	//__m256d avx3d = _mm256_mul_pd(avx1d, avx2d);
	__m256d avx3d = _mm256_div_pd(avx1d, avx2d);

	// AVX-512
	// NOTE : If your hardware is not capable of AVX-512, the following code will get an illegal instruction AKA crash.
	__m512d avx512_1 = { 1,2,3,4,5,6,7,8 };
	__m512d avx512_2 = { 1,2,3,4,5,6,7,8 };
	__m512d avx512_3 = _mm512_div_pd(avx512_1, avx512_2);


	system("pause");
}



