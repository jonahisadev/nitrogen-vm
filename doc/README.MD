# Nitrogen Virtual Machine

This is the official documentation for the Nitrogen Virtual Machine.
This is **NOT** documentation for the Nitrogen Language. 

## Basic Information

* 32-bit runtime/compiler
* Instructions and data are big-endian
* Program returns value in EBX
* Only one data section is allowed
* The default entry point is `start`

## Syntax

Below is the contents of the `tests/doc.n`.

```
#entry main

#section TEXT

main:
	ldd eax $a
	store eax
	ldd eax $b
	store eax
	call @add_nums
	mov ebx edx
	sub esp 8
	ncall %kill
	
; Add two numbers
add_nums:
	addr eax (ebp)+8
	addr ebx (ebp)+12
	add eax ebx
	mov edx eax
	ret
	
#section DATA

a: dd 40
b: dd 2
```
A few things to note:
* The default `const` and `add` instructions default to 32-bit sized
values. Looking at [Instructions](#instructions) section will show
that prefixes can be applied to specifize size of data. No prefix will default 32-bit values.
* Calling local labels (or jumping) requires a `@` to be prepended
to the label name.
* Calling a native function requires a `%` to be prepended to the label name.
* Addresses are taken as such `(data)+offset` where the offset is
the offset in memory.
* Comments start with `;`
* Variables are declared the same as labels but must be in the data section.
* Variables are referenced by prepending a `$` to the name of the variable.
* Sections are declared with the `#section` preprocessor.
* Entry points are declared with the `#entry` preprocessor. The default entry label is `start`

The above program loads two variables and pushes them to the stack 
and then calls an adding sub routine. The sub routine gets the two 
arguments from the stack and puts them in registers. Using the `add`
instruction, it adds the two arguments together, and sets `edx` as 
the return value. It then returns, where the result is moved into 
`ebx` to be returned by the program. A native call to `kill` 
(unnecessary with the `exit` instruction) ends the program.


## Instructions

| Byte Size | Prefix | Name |
| :-------: | :----: | ---- |
| 1			| B		 | Byte |
| 2			| W		 | Word |
| 4			| I		 | Integer |

The above table applies the first 9 instructions below

| Opcode 	| Arguments | Explanation |
| --------- | --------- | ----------- |
| CONST 	| N			| Push a number to the stack |
| LOAD		| R			| Pop a number to a register |
| STORE 	| R			| Push a number from a register |
| MOV		| R , R / N	| Move a constant or register value to register |
| ADD		| R , R / N | Add a constant or register value to register |
| SUB		| R , R / N	| Subtract a constant or register value to register |
| MUL		| R , R / N	| Multiply a constant or register value to register |
| DIV		| R , R / N	| Subtract a constant or register value to register. Remainder goes in ERM |
| ADDR		| R, A		| Move an address to a register |
| DB		| N			| Store a byte in variable memory |
| DW		| N			| Store a word in variable memory |
| DD		| N			| Store an integer in variable memory |
| LDB		| R, V		| Load a byte variable into a register |
| LDW		| R, V		| Load a word variable into a register |
| LDD		| R, V		| Load a integer variable into a register |
| JMP		| LBL		| Jump to a label |
| CALL		| LBL		| Call a label |
| RET		|			| Return from a call |
| NCALL		| NLBL		| Call C function |
| CMP		| R , R / N | Compare two values |
| JL		| LBL		| Jump if comparison is less than |
| JLE		| LBL		| Jump if comparison is less than or equal |
| JG		| LBL		| Jump if comparison is greater than |
| JGE		| LBL		| Jump if comparison is greater than or equal |
| JE		| LBL		| Jump if comparison is equal |
| JNE		| LBL		| Jump if comparison is not equal |
| EXIT		|			| Exit the program |

## Call Frame

Below is the specification for calling subroutines

### Calling

* Push arguments in reverse
* Push address of next instruction (done by runtime)
* Push base pointer, and set it to the stack pointer (done by runtime)

### Returning

* Clean stack from allocated local variables
* Set base pointer back to original (done by runtime)
* Set the program counter to the return address (done by runtime)

| Stack |
| ----- |
| Local variable 2
| Local variable 1 |
| EBP |
| Return address |
| 1st argument |
| 2nd argument |
| 3rd argument |

## Header

The header for a nitrogen binary file goes as follows:

* 2 byte "verification" number (0x4E37) which is 'N7' in ASCII
* 5 byte variable loading address to call
* 5 byte entry address jump instruction