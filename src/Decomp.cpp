#include <Nitrogen/Decomp.h>

namespace Nitrogen {

	Decomp::Decomp(unsigned char* prog, int len) {
		this->prog = prog;
		this->bin_size = len;
	}
	
	Decomp::~Decomp() {
		delete[] this->prog;
	}
	
	void Decomp::start() {
		int opcode;
		while (this->pc < this->bin_size) {
			opcode = prog[pc];
			
			printf("%08X: ", pc);
			switch (opcode) {
				// ICONST
				case _ICONST: {
					printf("ICONST \t%d", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// ILOAD
				case _ILOAD: {
					printf("ILOAD \t%s", Bytecode::getRegister(getNext()));
					break;
				}
				
				// ISTORE
				case _ISTORE: {
					printf("ISTORE \t%s", Bytecode::getRegister(getNext()));
					break;
				}
				
				// IMOV
				case _IMOV_R: {
					printf("IMOV \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _IMOV_N: {
					printf("IMOV \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
			}
			printf("\n");
			
			pc++;
		}
	}

	unsigned char Decomp::getNext() {
		return prog[++pc];
	}

}