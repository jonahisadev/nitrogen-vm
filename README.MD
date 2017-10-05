# Nitrogen

## Description

Yet another VM language

## Dev Notes

This will eventually be moved to a separate document, but for now,
this will remain easy to access.

### Adding Opcodes

* Add to ```TokenInst``` in Token.h
* Add to ```isInstruction``` in Token.cpp
	* If desired, add to ```printTokenList``` 
* Add bytecode to Bytecode.h
* Implement in Compiler.cpp
* Add to Decomp.cpp
* Implement behavior in Runtime.cpp

### To Do

This will always stay in README. Everything below this should move
to a separate document later.

* Do some address things
* Work on implementing native calls
* Add more of the opcodes listed below

### Instructions

| Opcode 	| Arguments | Explanation |
| --------- | --------- | ----------- |
| ICONST 	| N			| Push a 4 byte number to the stack |
| ILOAD		| R			| Pop a 4 byte number to a register |
| ISTORE 	| R			| Push a 4 byte number from a register |
| IMOV		| R , R / N	| Move a constant or register value to register|
| JMP		| LBL		| Jump to a label |
| CALL		| LBL		| Call a label |
| RET		|			| Return from a call |

### Call Frame

Below is the specification for calling subroutines

#### Calling

* Push arguments in reverse
* Push address of next instruction (done by runtime)
* Push base pointer, and set it to the stack pointer (done by runtime)

#### Returning

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