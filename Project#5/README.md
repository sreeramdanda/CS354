# Project #5
The goal of this project was to build a Dynamic Memory Allocator in the C programming language. All files were initally provided except the moap_functions.c file.
This file contains two functions: the first function allocates memory similar to malloc() found in the C programming language and the second function immitates the
free() function. The memory allocating function allocates memory using the first-fit method of allocation.
The free function frees memory through immediate coalescing.

The exacutable is made with the following command using GDB:<br>
`gcc -g mem_init.c mem_functions.c driver_alloc_8.c -Wall`<br>

The executable can be run using this command:<br>
`./a.out`

Note that the driver file can be replaced with any of the provided drives for testing.
