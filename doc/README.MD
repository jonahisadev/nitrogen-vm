# Nitrogen Virtual Machine

This is the official documentation for the Nitrogen Virtual Machine.
This is **NOT** documentation for the Nitrogen Language.

## Table of Contents
* [Basic Information](#basic-information)
* [Syntax](#syntax)
* [Instructions](#instructions)
* [Heap Allocation](#heap-allocation)
* [Call Frame](#call-frame)
* [Header](#header)

---

## Basic Information

* 32-bit runtime/compiler
* Instructions and data are big-endian
* Program returns value in EBX
* Only one data section is allowed
* The default entry point is `start`

---

## Syntax

Below is the contents of the `tests/doc.nvm`.

```
#entry main

#section TEXT

main:
	lds eax $str

	pusha
	store eax
	call @print_str
	add esp 4
	popa

	mov ebx 0
	exit

print_str:
	get eax (ebp)+8
loop:
	bget ebx (eax)
	cmp ebx 0
	je @end
	bstore ebx
	ncall %sys.print_char
	add esp 1
	inc eax
	jmp @loop
end:
	ret

#section DATA
str: ds "Hello world!" db 10 db 0
```
A few things to note:
* The default `store` and `add` instructions default to 32-bit sized
values. Looking at [Instructions](#instructions) section will show
that prefixes can be applied to specifize size of data. No prefix will default 32-bit values.
* Calling local labels (or jumping) requires a `@` to be prepended
to the label name.
* Calling a native function requires a `%` to be prepended to the label name.
	* The library name goes before the period, and the function name goes after
	* The above code calls `print_char` from the `sys` library (loaded by default)
* Addresses are taken as such `(data)+offset` where the offset is
the offset in memory.
* Comments start with `;`
* Variables are declared the same as labels but must be in the data section.
* Variables are referenced by prepending a `$` to the name of the variable.
* Sections are declared with the `#section` preprocessor.
* Entry points are declared with the `#entry` preprocessor. The default entry label is `start`
* Functions return their value in the `ERX` register.

For a more in depth explanation of what this specific program does, please read
the actual file. There's info at the top.

---

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
| GET		| R , A		| Get values from RAM using registers as pointers |
| SET		| A , R / N	| Set register or constant value in RAM |
| DB		| N			| Store a byte in variable memory |
| DW		| N			| Store a word in variable memory |
| DD		| N			| Store an integer in variable memory |
| DS		| STR		| Store a string in variable memory |
| LDB		| R, V		| Load a byte variable into a register |
| LDW		| R, V		| Load a word variable into a register |
| LDD		| R, V		| Load a integer variable into a register |
| LDS		| R, V		| Load a pointer to a string into a register |
| JMP		| LBL		| Jump to a label |
| CALL		| LBL		| Call a label |
| RET		|			| Return from a call |
| MALLOC	| N	/ R		| Heap allocate a certain number of bytes |
| FREE		|			| Pops an address and frees that heap address |
| NCALL		| NLBL		| Call C function |
| INC		| R			| Increment a register's value |
| DEC		| R			| Decrement a register's value |
| PUSHA		|			| Push all general registers except ERX |
| POPA		|			| Pop all general registers except ERX |
| CMP		| R , R / N | Compare two values |
| JL		| LBL		| Jump if comparison is less than |
| JLE		| LBL		| Jump if comparison is less than or equal |
| JG		| LBL		| Jump if comparison is greater than |
| JGE		| LBL		| Jump if comparison is greater than or equal |
| JE		| LBL		| Jump if comparison is equal |
| JNE		| LBL		| Jump if comparison is not equal |
| EXIT		|			| Exit the program |

---

## Heap Allocation

There are two instructions that deal with heap allocation: `MALLOC` and `FREE`.
`MALLOC` takes a number argument after, which is the amount of bytes to be
allocated. After the memory is allocated, the address of the memory is pushed
to the stack.

`FREE` takes no arguments. The address of the originally malloc'd memory must
be pushed to the stack, and the `FREE` instruction will take that address and
free it for future use.

---

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
| 3rd argument |
| 2nd argument |
| 1st argument |
| Return Address |
| EBP |
| Local variable 1 |
| Local variable 2 |

---

## Header

The header for a nitrogen binary file goes as follows:

* 2 byte "verification" number (0x4E37) which is 'N7' in ASCII
* 5 byte variable loading address to call
* 1 byte instruction to initalize the heap
* 5 byte entry address jump instruction