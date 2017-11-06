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
		
		if (prog[0] == 'N' && prog[1] == '7') {
			pc += 2;
		} else {
			printf("ERR: Invalid Nitrogen Binary\n");
			exit(1);
		}
		
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
				
				// IADD
				case ByteInst::_IADD_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					*a += *b;
					break;
				}
				case ByteInst::_IADD_N: {
					unsigned int* reg = getRegister(getNext());
					*reg += (unsigned int)Util::atoi(getNext(), getNext(), getNext(), getNext());
					break;
				}
				
				// ISUB
				case ByteInst::_ISUB_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					*a -= *b;
					break;
				}
				case ByteInst::_ISUB_N: {
					unsigned int* reg = getRegister(getNext());
					*reg -= (unsigned int)Util::atoi(getNext(), getNext(), getNext(), getNext());
					break;
				}
				
				// IMUL
				case ByteInst::_IMUL_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					*a *= *b;
					break;
				}
				case ByteInst::_IMUL_N: {
					unsigned int* reg = getRegister(getNext());
					*reg *= (unsigned int)Util::atoi(getNext(), getNext(), getNext(), getNext());
					break;
				}
				
				// IDIV
				case ByteInst::_IDIV_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					if (*b == 0) {
						printf("ERR: Div by 0");
						this->ebx = 1;
						goto exit;
					}
					
					unsigned int r = (unsigned int)floor(*a % *b);
					
					*a /= *b;
					this->erm = r;
					break;
				}
				case ByteInst::_IDIV_N: {
					unsigned int* reg = getRegister(getNext());
					unsigned int num = Util::atoi(getNext(), getNext(), getNext(), getNext());
					
					if (num == 0) {
						printf("ERR: Div by 0");
						this->ebx = 1;
						goto exit;
					}
					
					unsigned int r = (unsigned int)floor(*reg % num);
					
					*reg /= num;
					this->erm = r;
					break;
				}
				
				// IADDR
				case ByteInst::_IADDR_RA: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					int off = getNext();
					// printf("%d, %d, %d, %d\n", ram[*src + off + 0], ram[*src + off + 1], ram[*src + off + 2], ram[*src + off + 3]);
					*dest = (unsigned int)Util::atoi(ram[*src + off + 0], ram[*src + off + 1], ram[*src + off + 2], ram[*src + off + 3]);
					break;
				}
				case ByteInst::_IADDR_RS: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					int off = getNext();
					// printf("%d, %d, %d, %d\n", ram[*src - off + 0], ram[*src - off + 1], ram[*src - off + 2], ram[*src - off + 3]);
					*dest = (unsigned int)Util::atoi(ram[*src - off + 0], ram[*src - off + 1], ram[*src - off + 2], ram[*src - off + 3]);
					break;
				}
				
				// WCONST
				case ByteInst::_WCONST: {
					pushw(getNext(), getNext());
					break;
				}
				
				// WLOAD
				case ByteInst::_WLOAD: {
					unsigned int* reg = getRegister(getNext());
					*reg = popw();
					break;
				}
				
				// WSTORE
				case ByteInst::_WSTORE: {
					unsigned int* reg = getRegister(getNext());
					pushw((unsigned short)*reg);
					break;
				}
				
				// WMOV
				case ByteInst::_WMOV_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					*a = *b;
					break;
				}
				case ByteInst::_WMOV_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = (unsigned short)Util::atow(getNext(), getNext());
					break;
				}
				
				// WADD
				case ByteInst::_WADD_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					*a = ((unsigned short)*a + (unsigned short)*b);
					
					break;
				}
				case ByteInst::_WADD_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = ((unsigned short)*reg + (unsigned short)Util::atow(getNext(), getNext()));
					break;
				}
				
				// WSUB
				case ByteInst::_WSUB_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					*a = ((unsigned short)*a - (unsigned short)*b);
					
					break;
				}
				case ByteInst::_WSUB_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = ((unsigned short)*reg - (unsigned short)Util::atow(getNext(), getNext()));
					break;
				}
				
				// WMUL
				case ByteInst::_WMUL_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					*a = ((unsigned short)*a * (unsigned short)*b);
					
					break;
				}
				case ByteInst::_WMUL_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = ((unsigned short)*reg * (unsigned short)Util::atow(getNext(), getNext()));
					break;
				}
				
				// WDIV
				case ByteInst::_WDIV_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					if (*b == 0) {
						printf("ERR: Div by 0");
						this->ebx = 1;
						goto exit;
					}
					
					unsigned int r = (unsigned int)floor(*a % *b);
					
					*a = ((unsigned short)*a / (unsigned short)*b);
					this->erm = r;
					break;
				}
				case ByteInst::_WDIV_N: {
					unsigned int* reg = getRegister(getNext());
					unsigned short num = Util::atow(getNext(), getNext());
					
					if (num == 0) {
						printf("ERR: Div by 0");
						this->ebx = 1;
						goto exit;
					}
					
					unsigned int r = (unsigned short)floor(*reg % num);
					
					*reg = (unsigned short)*reg/num;
					this->erm = r;
					break;
				}
				
				// WADDR
				case ByteInst::_WADDR_RA: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					int off = getNext();
					*dest = (unsigned short)Util::atow(ram[*src + off + 0], ram[*src + off + 1]);
					break;
				}
				case ByteInst::_WADDR_RS: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					int off = getNext();
					*dest = (unsigned short)Util::atow(ram[*src - off + 0], ram[*src - off + 1]);
					break;
				}
				
				// DB
				case ByteInst::_DB: {
					ram[GLOBAL_START + vsize] = getNext();
					vsize++;
					break;
				}
				
				// DW
				case ByteInst::_DW: {
					ram[GLOBAL_START + vsize + 0] = getNext();
					ram[GLOBAL_START + vsize + 1] = getNext();
					vsize += 2;
					break;
				}
				
				// DD
				case ByteInst::_DD: {
					ram[GLOBAL_START + vsize + 0] = getNext();
					ram[GLOBAL_START + vsize + 1] = getNext();
					ram[GLOBAL_START + vsize + 2] = getNext();
					ram[GLOBAL_START + vsize + 3] = getNext();
					vsize += 4;
					break;
				}
				
				// LDB
				case ByteInst::_LDB: {
					unsigned int* reg = getRegister(getNext());
					int addr = GLOBAL_START + Util::atoi(getNext(), getNext(), getNext(), getNext());
					*reg = ram[addr];
					break;
				}
				
				// LDW
				case ByteInst::_LDW: {
					unsigned int* reg = getRegister(getNext());
					int addr = GLOBAL_START + Util::atoi(getNext(), getNext(), getNext(), getNext());
					*reg = Util::atow(ram[addr], ram[addr + 1]);
					break;
				}
				
				// LDD
				case ByteInst::_LDD: {
					unsigned int* reg = getRegister(getNext());
					int addr = GLOBAL_START + Util::atoi(getNext(), getNext(), getNext(), getNext());
					*reg = Util::atoi(ram[addr], ram[addr + 1], ram[addr + 2], ram[addr + 3]);
					break;
				}
				
				// STB
				case ByteInst::_STB_VR: {
					int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* reg = getRegister(getNext());
					ram[GLOBAL_START + addr] = *reg;
					break;
				}
				case ByteInst::_STB_VN: {
					int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					ram[GLOBAL_START + addr] = getNext();
					break;
				}
				
				// STW
				case ByteInst::_STW_VR: {
					int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* reg = getRegister(getNext());
					unsigned char* data = Util::wtoa(*reg);
					ram[GLOBAL_START + addr + 0] = data[0];
					ram[GLOBAL_START + addr + 1] = data[1];
					delete[] data;
					break;
				}
				case ByteInst::_STW_VN: {
					int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					ram[GLOBAL_START + addr + 0] = getNext();
					ram[GLOBAL_START + addr + 1] = getNext();
					break;
				}
				
				// STD
				case ByteInst::_STD_VR: {
					int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* reg = getRegister(getNext());
					unsigned char* data = Util::itoa(*reg);
					ram[GLOBAL_START + addr + 0] = data[0];
					ram[GLOBAL_START + addr + 1] = data[1];
					ram[GLOBAL_START + addr + 2] = data[2];
					ram[GLOBAL_START + addr + 3] = data[3];
					delete[] data;
					break;
				}
				case ByteInst::_STD_VN: {
					int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					ram[GLOBAL_START + addr + 0] = getNext();
					ram[GLOBAL_START + addr + 1] = getNext();
					ram[GLOBAL_START + addr + 2] = getNext();
					ram[GLOBAL_START + addr + 3] = getNext();
					break;
				}
				
				// JMP
				case ByteInst::_JMP: {
					this->pc = Util::atoi(getNext(), getNext(), getNext(), getNext()) - 1;
					break;
				}
				
				// CMP
				case ByteInst::_CMP_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					compare(*a, *b);
					break;
				}
				case ByteInst::_CMP_N: {
					unsigned int* reg = getRegister(getNext());
					unsigned int val = Util::atoi(getNext(), getNext(), getNext(), getNext());
					
					compare(*reg, val);
					break;
				}
				
				// BRANCHES
				case ByteInst::_JL: {
					unsigned int go = Util::atoi(getNext(), getNext(), getNext(), getNext());
					if (getCompare(1))
						this->pc = go - 1;
					break;
				}
				case ByteInst::_JG: {
					unsigned int go = Util::atoi(getNext(), getNext(), getNext(), getNext());
					if (getCompare(2))
						this->pc = go - 1;
					break;
				}
				case ByteInst::_JLE: {
					unsigned int go = Util::atoi(getNext(), getNext(), getNext(), getNext());
					if (getCompare(1) || getCompare(3))
						this->pc = go - 1;
					break;
				}
				case ByteInst::_JGE: {
					unsigned int go = Util::atoi(getNext(), getNext(), getNext(), getNext());
					if (getCompare(2) || getCompare(3))
						this->pc = go - 1;
					break;
				}
				case ByteInst::_JE: {
					unsigned int go = Util::atoi(getNext(), getNext(), getNext(), getNext());
					if (getCompare(3))
						this->pc = go - 1;
					break;
				}
				case ByteInst::_JNE: {
					unsigned int go = Util::atoi(getNext(), getNext(), getNext(), getNext());
					if (!getCompare(3))
						this->pc = go - 1;
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
				
				// INC
				case ByteInst::_INC: {
					unsigned int* reg = getRegister(getNext());
					*reg += 1;
					break;
				}
				
				// DEC
				case ByteInst::_DEC: {
					unsigned int* reg = getRegister(getNext());
					*reg -= 1;
					break;
				}
				
				// PUSHA
				case ByteInst::_PUSHA: {
					pushi(*(getRegister(_EAX)));
					pushi(*(getRegister(_EBX)));
					pushi(*(getRegister(_ECX)));
					//pushi(*(getRegister(_EDX)));
					pushi(*(getRegister(_ERM)));
					break;
				}
				
				// POPA
				case ByteInst::_POPA: {
					*(getRegister(_ERM)) = popi();
					//*(getRegister(_EDX)) = popi();
					*(getRegister(_ECX)) = popi();
					*(getRegister(_EBX)) = popi();
					*(getRegister(_EAX)) = popi();
					break;
				}
				
				// NCALL
				case ByteInst::_NCALL: {
					char* name = new char[256];
					char c;
					int x = 0;
					while ((c = getNext()) != '\0')
						name[x++] = c;
					
					pushi(this->pc);
					pushi(this->bp);
					this->bp = this->sp;
					
					this->edx = lsystem->callFunction(name);
					
					this->bp = popi();
					this->pc = popi();
					
					delete[] name;
					break;
				}
				
				// EXIT
				case ByteInst::_EXIT: {
					goto exit;
				}
			}
			
			// printf("STACK: [%d, %d, %d, %d]\n", ram[bp], ram[bp-1], ram[bp-2], ram[bp-3]);
			
			pc++;
			
			if (pc >= bin_size)
				break;
		}
		
		exit:
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
	
	void Runtime::pushw(unsigned char a, unsigned char b) {
		ram[--sp] = b;
		ram[--sp] = a;
	}
	
	void Runtime::pushw(short x) {
		unsigned char* arr = Util::wtoa(x);
		pushw(arr[0], arr[1]);
		delete[] arr;
	}
	
	short Runtime::popw() {
		unsigned char a = ram[sp++];
		unsigned char b = ram[sp++];
		
		return Util::atow(a, b);
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
			case _ERM: 
				return &erm;
			case _ESP:
				return &sp;
			case _EBP:
				return &bp;
			default:
				return nullptr;
		}
	}
	
	// Less = 		0001
	// Greater =	0010
	// Equal = 		0100
	
	bool Runtime::getCompare(int place) {
		return (this->cmpflag >> (place - 1)) & 0x1;
	}
	
	void Runtime::compare(int a, int b) {
		if (a == b)
			this->cmpflag |= 0b100;
		else
			this->cmpflag &= 0b011;
		
		if (a < b)
			this->cmpflag |= 0b001;
		else
			this->cmpflag &= 0b110;
			
		if (a > b)
			this->cmpflag |= 0b010;
		else	
			this->cmpflag &= 0b101;
	}
	
	unsigned char Runtime::getNext() {
		return prog[++pc];
	}

}