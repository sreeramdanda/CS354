	.file	"find_max_template.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"The length of the array is %d\n"
	.text
	.globl	Find_Max
	.type	Find_Max, @function
Find_Max:
// prologue - write code for the prologue here
    endbr64
    push    %rbp
    movq    %rsp, %rbp
    subq    $32,  %rsp              # make space for local variables

// printf("The length of the array is %d\n", n);
// update this code if necessary to print the length of the array
// this block prints the value of register %edi
// initially the parameter n
	movl	%edi, -4(%rbp)          # store array length on stack
    movq    %rsi, -12(%rbp)         # store address of array pointer on stack
  
    movl	-4(%rbp),   %esi          # prints array length
	leaq	.LC0(%rip), %rdi
	movl	$0,         %eax
	call	printf@PLT

// reserve space for local variables
/* make a table here the variables from 
 * your c code and the addresses used in assembly 
 * n (length)    - address of n: -4(%rbp)   
 * a (array*)    - address of a: -12(%rbp)
 * i (index)     - address of i: -16(%rbp)
 * m (max_index) - address of m: -20(%rbp)
 * ....
*/ 
    movl    $1, -16(%rbp)           # store index counter on stack
    movl    $0, -20(%rbp)           # store maximum value index on stack

// this code calls Print_One_Number to 
// print the number found in register %eax - use this code to debug 
// replace $999 with a register or memory address you wish to print
//    movl    -4(%rbp), %eax
//	movl	%eax, %edi
//	call	Print_One_Number@PLT

// write your code to find the index of the maximum value here
    jmp     COND                    # Begin the loop iteration to find max

UPDATE_MAX:                     
    movl    -16(%rbp), %eax         # Update the index for maximum value
    movl    %eax,      -20(%rbp)

BODY:
    movl    -20(%rbp),       %edx   # Index of the maxmimum value
    movq    -12(%rbp),       %rax   # Address of the maximum value
    movl    (%rax, %rdx, 4), %ecx   # Value of the maximum value

    movl    -16(%rbp),       %edx   # Current index of the loop
    movl    (%rax, %rdx, 4), %edx   # Value at the current index

    cmpl    %ecx, %edx              # Compare the two values
    jg      UPDATE_MAX              # Update new max if current value is greater

    movl    -16(%rbp), %edx         # Increment Index
    addl    $1,        %edx
    movl    %edx,      -16(%rbp)

COND:                               # Loop from index = 1 to index = length of array
    movl    -16(%rbp), %edx         # Check if index is within loop, leave if equal or greater
    cmpl    -4(%rbp),  %edx
    js      BODY                    # If valid index, perform maximum check

// prepare the return value
// the template returns -1, you will need to update this
	movl	-20(%rbp), %eax         # Return the maximum value's index

// epilogue - complete the epilogue below
	addq    $32, %rsp               # Restore the stack pointer
    popq    %rbp
    ret

.LFE0:
	.size	Find_Max, .-Find_Max
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
