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

* Implement calling
	* Write out a call frame standard
* Fix some parsing bugs with new-lines
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