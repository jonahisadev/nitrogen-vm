# Nitrogen

## Description

Yet another VM language

## Dev Notes

This will eventually be moved to a separate document, but for now,
this will remain easy to access.

### To Do

This will always stay in README. Everything below this should move
to a separate document later.

* Decompiler
* Add more of the opcodes listed below

### Instructions

| Opcode 	| Arguments | Explanation |
| --------- | --------- | ----------- |
| ICONST 	| N			| Push a 4 byte number to the stack |
| ILOAD		| R			| Pop a 4 byte number to a register |
| ISTORE 	| R			| Push a 4 byte number from a register |
| IMOV		| R , R / N	| Move a constant or register value to register|