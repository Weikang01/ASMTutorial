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

***32 bit 80386**************************************************

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

***Pentium !V And x64********************************************

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

#include <iostream>
#define pause system("pause")

extern "C" int SomeFunction();

void main()
{
	std::cout << SomeFunction() << std::endl;
	pause;
}