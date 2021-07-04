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
...32 bit 80386...................................................

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
...Pentium !V And x64.............................................

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
...Fundamental Data Types.........................................
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
...MOV and LEA....................................................
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
...ADD, SUB INC and DEC...........................................
ADD, SUB INC and DEC

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

#include <iostream>

extern "C" int AddSubTestFunction();

int main()
{
	AddSubTestFunction();
}