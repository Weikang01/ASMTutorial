;.data
;text db "Hello, World!", 10
; text: This is a name assigned to the address in memory that this data is located in. Whenever we use "text" later in the code, when the code is compiled, the compiler will determine the actual location in memory of this data and replace all future instance of "text" with that memory address.
; db: "db" stands for "defined byte". It essentially means that we are going to define some raw bytes of data to insert into our code.
; "Hello, World!", 10: This is the bytes of data we are defining. Each character in the string of text is a single byte. The "10" is a newline character, which denote as "\n"
; Registers
; Registers are part of the processor that temporarily holds the memory.
; In the x86_64 architecture, registers hold 64 bits.
; This means each register can hold the values:
; Unsigned:    0 - 2^64
; Signed:  -2^63 - 2^63-1
;____________________________
;|8-bit|16-bit|32-bit|64-bit|
;|al   |ax    |eax   |rax   |
;|bl   |bx    |ebx   |rbx   |
;|cl   |cx    |ecx   |rcx   |
;|dl   |dx    |edx   |rdx   |
;|sil  |si    |esi   |rsi   |
;|dil  |di    |edi   |rdi   |
;|bpl  |bp    |ebp   |rbp   |
;|spl  |sp    |esp   |rsp   |
;|r8b  |r8w   |r8d   |r8    |
;|r9b  |r9w   |r9d   |r9    |
;|r10b |r10w  |r10d  |r10   |
;|r11b |r11w  |r11d  |r11   |
;|r12b |r12w  |r12d  |r12   |
;|r13b |r13w  |r13d  |r13   |
;|r14b |r14w  |r14d  |r14   |
;|r15b |r15w  |r15d  |r15   |
;
;System Call
;A system call, or a syscall, is when a program requests a service from the Kernel.
;System calls will differ by operating system because different operating systems use different kernels.
;All syscalls have an ID associated with them (a number).
;Syscalls also take arguments, meaning, a list of inputs.
;
;System Call Inputs by Register
;_____________________
;|Argument |Registers|
;|ID       |rax      |
;|1	       |rdi      |
;|2	       |rsi      |
;|3	       |rdx      |
;|4	       |r10      |
;|5	       |r8       |
;|6        |r9       |
;
;global _main
;extern _printf
;
;section .text
;
;.code
;HelloWorld proc
;	mov rax, 1
;	mov rdx, 1
;	mov rsi, text
;	mov rdx, 14
;	syscall
;
;	mov rax, 60
;	mov rdi, 0
;	syscall
;	ret
;HelloWorld endp
;end