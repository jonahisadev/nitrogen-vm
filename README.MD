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

* Add instructions:
	* Byte instructions
	* Variable declarations
		* Strings
* Heap allocation
* Better semantics and error handling
* Implement includes, loads, etc
	* Include separate source files
	* Load external libraries
* Runtime debugger
* Work on implementing native calls
	* First be able to load libraries from NSM
	* Create a sort of API for external C code