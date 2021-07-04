/*
8086 Registers

The 8086 hit the world in 1978 and was incredibly popular. It was a 16 bit processor, which means most of its general purpose registers are 16 bits, and most of its instructions operate on 16 bits.

** General Purpose Registers (GPR)
AX/BX/CX/DX
AX/DX : Used For Arithmetic Operations Like Division, etc.
CX : Used For Index In A Loop

** Index Registers
SI/DI/BP/SP
SI : Source Index
DI : Destination Index
BP : Base Pointer
SP : Stack Pointer

** Instruction Pointer (Program Counter)
IP : Point In RAM Where The Instruction Are Being Read From

** Segment Registers
CS/DS/ES/SS
Segment Registers Are Used By The Operating System For Various Incidental Things, Like Paging Information and Threading Information.

** Flags Register
Flags
Stores The Stats Of Comparisons And Other Instructions So We Can Act On That Stat.

*/

#include <iostream>
#define pause system("pause")

extern "C" int SomeFunction();

void main()
{
	std::cout << SomeFunction() << std::endl;
	pause;
}