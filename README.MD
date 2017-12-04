# Nitrogen

## Description

Yet another VM language

## Dev Notes

Language support for [Atom](https://atom.io/packages/language-nitrogen-vm)

### Adding Opcodes

* Add to ```TokenInst``` in Token.h
* Add to ```isInstruction``` in Token.cpp
	* If desired, add to ```printTokenList``` 
* Add bytecode to Bytecode.h
* Implement in Compiler.cpp
* Add to Decomp.cpp
* Implement behavior in Runtime.cpp

### To Do

Here are the current features to add for Nitrogen:

* Work on implementing native calls
	* First be able to load libraries from NSM
	* Create a sort of API for external C code
* Floats

Below are general features that should be added:

* Include separate source files
* Runtime debugger