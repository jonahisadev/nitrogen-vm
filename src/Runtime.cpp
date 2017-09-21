#include <Nitrogen/Runtime.h>

namespace Nitrogen {

	Runtime::Runtime(unsigned char* prog, int bin_size) {
		this->prog = prog;
		this->bin_size = bin_size;
		this->ram = new unsigned char[RAM_SIZE];
	}
	
	Runtime::~Runtime() {
		delete[] prog;
	}
	
	int Runtime::start() {
		int opcode;
		
		while (true) {
			opcode = prog[pc];
			
			switch (opcode) {
				case ByteInst::_ICONST: {
					pushi(prog[pc+1], prog[pc+2], prog[pc+3], prog[pc+4]);
					pc += 4;
					break;
				}
			}
			
			//printf("STACK: [%d, %d, %d, %d]\n", ram[sp], ram[sp+1], ram[sp+2], ram[sp+3]);
			
			pc++;
			
			if (pc >= bin_size)
				break;
		}
		
		return 0;
	}
	
	void Runtime::pushi(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
		ram[--sp] = d;
		ram[--sp] = c;
		ram[--sp] = b;
		ram[--sp] = a;
	}

}