.code
ControlStatements proc
	;;;(if statement) C code
	;;int a = 5;
	;;int b = 7;
	;;int c = 0;
	;;if (a < b && a == 10)
	;;	c = 1;
	;mov eax, 5
	;mov ebx, 7
	;mov ecx, 0  ; result of both conditions
	;mov r8d, 0
	;mov edx, 1
	;cmp eax, ebx
	;cmovl ecx, edx  ; Move 1 into ecx if a < b
	;cmp eax, 10
	;cmove r8d, edx  ; Move 1 into r8d if a == 10
	;and ecx, r8d

	;;;(while loop) C code
	;;int i = 0;
	;;while (i < 3)
	;;{
	;;	i++;
	;;}
	;mov eax, 0
	;cmp eax, 3
	;jge Finished
	;LoopHead:
	;; Body of the while loop
	;inc eax
	;cmp eax, 3
	;jl LoopHead
	;Finished:

	;;;(do while loop) C code
	;;int i = 0;
	;;do
	;;{
	;;	i++;
	;;} while (i < 3);
	;mov eax, 0
	;mov edx, 3
	;LoopHead:
	;inc eax
	;cmp eax, edx
	;jl LoopHead
	
	;;;Common Assembly loop
	;mov ecx, 5
	;LoopHead:
	;; Body of the loop
	;dec ecx
	;jnz LoopHead

	;;;(for loop) C code
	;;for (int i = 0; i < 3; i++)
	;;{
	;;}
	;mov eax, 0
	;LoopHead:
	;cmp eax, 3
	;jge Finished
	;inc eax
	;jmp LoopHead
	;Finished:

	ret
ControlStatements endp



end