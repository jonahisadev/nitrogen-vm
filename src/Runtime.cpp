#include <Nitrogen/Runtime.h>

namespace Nitrogen {

	Runtime::Runtime(unsigned char* prog, int bin_size) {
		this->prog = prog;
		this->bin_size = bin_size;
		this->ram = new unsigned char[RAM_SIZE];
		
		this->env = createEnvironment(
			ram,
			&sp,
			&bp,
			&eax,
			&ebx,
			&ecx,
			&edx
		);
		this->lsystem = new NativeLib("native/system.dylib");
		this->lsystem->bind(this->env);
	}
	
	Runtime::~Runtime() {
		delete[] prog;
	}
	
	int Runtime::start() {
		int opcode;
		
		while (true) {
			opcode = prog[pc];
			
			switch (opcode) {
				// ICONST
				case ByteInst::_ICONST: {
					pushi(getNext(), getNext(), getNext(), getNext());
					break;
				}
				
				// ILOAD
				case ByteInst::_ILOAD: {
					unsigned int* reg = getRegister(getNext());
					*reg = popi();
					break;
				}
				
				// ISTORE
				case ByteInst::_ISTORE: {
					unsigned int* reg = getRegister(getNext());
					pushi(*reg);
					break;
				}
				
				// IMOV
				case ByteInst::_IMOV_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					*a = *b;
					break;
				}
				case ByteInst::_IMOV_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = (unsigned int) Util::atoi(getNext(), getNext(), getNext(), getNext());
					break;
				}
				
				// JMP
				case ByteInst::_JMP: {
					this->pc = Util::atoi(getNext(), getNext(), getNext(), getNext()) - 1;
					break;
				}
				
				// CALL
				case ByteInst::_CALL: {
					pushi(this->pc + 4);		// Push return address
					pushi(this->bp);			// Push old base pointer
					this->bp = this->sp;		// Update base pointer
					this->pc = Util::atoi(getNext(), getNext(), getNext(), getNext()) - 1;
					break;
				}
				
				// RET
				case ByteInst::_RET: {
					this->bp = popi();			// Get the old base pointer back
					this->pc = popi();			// Go back to the return address
					break;
				}
				
				// NCALL
				case ByteInst::_NCALL: {
					char* name = new char[256];
					char c;
					int x = 0;
					while ((c = getNext()) != '\0')
						name[x++] = c;
					this->edx = lsystem->callFunction(name);
					delete[] name;
					break;
				}
			}
			
			//printf("STACK: [%d, %d, %d, %d]\n", ram[sp], ram[sp+1], ram[sp+2], ram[sp+3]);
			
			pc++;
			
			if (pc >= bin_size)
				break;
		}
		
		return ebx;
	}
	
	void Runtime::pushi(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
		ram[--sp] = d;
		ram[--sp] = c;
		ram[--sp] = b;
		ram[--sp] = a;
	}
	
	void Runtime::pushi(int x) {
		unsigned char* arr = Util::itoa(x);
		pushi(arr[0], arr[1], arr[2], arr[3]);
		delete[] arr;
	}
	
	int Runtime::popi() {
		unsigned char a = ram[sp++];
		unsigned char b = ram[sp++];
		unsigned char c = ram[sp++];
		unsigned char d = ram[sp++];
		
		return Util::atoi(a, b, c, d);
	}
	
	unsigned int* Runtime::getRegister(int code) {
		switch (code) {
			case _EAX:
				return &eax;
			case _EBX:
				return &ebx;
			case _ECX:
				return &ecx;
			case _EDX:
				return &edx;
			case _ESP:
				return &sp;
			case _EBP:
				return &bp;
			default:
				return nullptr;
		}
	}
	
	unsigned char Runtime::getNext() {
		return prog[++pc];
	}

}