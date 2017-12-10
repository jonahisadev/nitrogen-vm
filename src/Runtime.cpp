#include <Nitrogen/Runtime.h>

namespace Nitrogen {

	Runtime::Runtime(unsigned char* prog, int bin_size) {
		this->prog = prog;
		this->bin_size = bin_size;
		this->ram = new unsigned char[RAM_SIZE];
		
		// Set up native library and environment
		this->env = createEnvironment(
			ram,
			&sp,
			&bp,
			&eax,
			&ebx,
			&ecx,
			&edx,
			&erx,
			&erm
		);
		
		// Load system library
		this->sys = new NativeLib("native/system.dylib", "sys");
		this->sys->bind(env);

		// Initialize native library
		void (*initl)() = (void (*)())dlsym(this->sys->lib, "initl");
		initl();
	}
	
	Runtime::~Runtime() {
		delete[] this->prog;
		delete this->sys;
		delete[] this->ram;
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
				
				// BCONST
				case ByteInst::_BCONST: {
					pushb(getNext());
					break;
				}
				
				// BLOAD
				case ByteInst::_BLOAD: {
					unsigned int* reg = getRegister(getNext());
					*reg = popb();
					break;
				}
				
				// BSTORE
				case ByteInst::_BSTORE: {
					unsigned int* reg = getRegister(getNext());
					pushb((unsigned char)*reg);
					break;
				}
				
				// BMOV
				case ByteInst::_BMOV_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					*a = *b;
					break;
				}
				case ByteInst::_BMOV_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = getNext();
					break;
				}
				
				// BADD
				case ByteInst::_BADD_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					*a = ((unsigned char)*a + (unsigned char)*b);
					
					break;
				}
				case ByteInst::_BADD_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = ((unsigned char)*reg + getNext());
					break;
				}
				
				// BSUB
				case ByteInst::_BSUB_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					*a = ((unsigned char)*a - (unsigned char)*b);
					
					break;
				}
				case ByteInst::_BSUB_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = ((unsigned char)*reg - getNext());
					break;
				}
				
				// BMUL
				case ByteInst::_BMUL_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					*a = ((unsigned char)*a * (unsigned char)*b);
					
					break;
				}
				case ByteInst::_BMUL_N: {
					unsigned int* reg = getRegister(getNext());
					*reg = ((unsigned char)*reg * getNext());
					break;
				}
				
				// BDIV
				case ByteInst::_BDIV_R: {
					unsigned int* a = getRegister(getNext());
					unsigned int* b = getRegister(getNext());
					
					if (*b == 0) {
						printf("ERR: Div by 0");
						this->ebx = 1;
						goto exit;
					}
					
					unsigned int r = (unsigned int)floor(*a % *b);
					
					*a = ((unsigned char)*a / (unsigned char)*b);
					this->erm = r;
					break;
				}
				case ByteInst::_BDIV_N: {
					unsigned int* reg = getRegister(getNext());
					unsigned short num = getNext();
					
					if (num == 0) {
						printf("ERR: Div by 0");
						this->ebx = 1;
						goto exit;
					}
					
					unsigned int r = (unsigned short)floor(*reg % num);
					
					*reg = (unsigned char)*reg/num;
					this->erm = r;
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

				// DS
				case ByteInst::_DS: {
					unsigned char c;
					while ((c = getNext()) != '\0') {
						ram[GLOBAL_START + vsize] = c;
						vsize++;
					}
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

				// LDS
				case ByteInst::_LDS: {
					unsigned int* reg = getRegister(getNext());
					int addr = GLOBAL_START + Util::atoi(getNext(), getNext(), getNext(), getNext());
					*reg = addr;
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
					pushi(*(getRegister(_EDX)));
					pushi(*(getRegister(_ERM)));
					break;
				}
				
				// POPA
				case ByteInst::_POPA: {
					*(getRegister(_ERM)) = popi();
					*(getRegister(_EDX)) = popi();
					*(getRegister(_ECX)) = popi();
					*(getRegister(_EBX)) = popi();
					*(getRegister(_EAX)) = popi();
					break;
				}
				
				// HINIT
				case ByteInst::_HINIT: {
					HEAP_START = GLOBAL_START + vsize;
					HEAP_ROOT = new HeapNode(nullptr, nullptr, HEAP_START, HEAP_START);
					break;
				}
				
				// MALLOC
				case ByteInst::_MALLOC_R: {
					unsigned int* reg = getRegister(getNext());
					heap_alloc(*reg);
					break;
				}
				case ByteInst::_MALLOC_N: {
					unsigned int size = Util::atoi(getNext(), getNext(), getNext(), getNext());
					heap_alloc(size);
					break;
				}
				
				// IGET
				case ByteInst::_IGET_A: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					*dest = (unsigned int)Util::atoi(ram[*src + off + 0], ram[*src + off + 1], ram[*src + off + 2], ram[*src + off + 3]);
					break;
				}
				case ByteInst::_IGET_S: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					*dest = (unsigned int)Util::atoi(ram[*src - off + 0], ram[*src - off + 1], ram[*src - off + 2], ram[*src - off + 3]);
					break;
				}
				
				// WGET
				case ByteInst::_WGET_A: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					*dest = (unsigned int)Util::atow(ram[*src + off + 0], ram[*src + off + 1]);
					break;
				}
				case ByteInst::_WGET_S: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					*dest = (unsigned int)Util::atow(ram[*src - off + 0], ram[*src - off + 1]);
					break;
				}
				
				// BGET
				case ByteInst::_BGET_A: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					*dest = ram[*src + off];
					break;
				}
				case ByteInst::_BGET_S: {
					unsigned int* dest = getRegister(getNext());
					unsigned int* src = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					*dest = ram[*src - off];
					break;
				}
				
				// ISET
				case ByteInst::_ISET_RA: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* src = getRegister(getNext());
					unsigned char* data = Util::itoa(*src);
					
					ram[*dest + off + 0] = data[0];
					ram[*dest + off + 1] = data[1];
					ram[*dest + off + 2] = data[2];
					ram[*dest + off + 3] = data[3];
					
					break;
				}
				case ByteInst::_ISET_RS: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* src = getRegister(getNext());
					unsigned char* data = Util::itoa(*src);
					
					ram[*dest - off + 0] = data[0];
					ram[*dest - off + 1] = data[1];
					ram[*dest - off + 2] = data[2];
					ram[*dest - off + 3] = data[3];
					
					break;
				}
				case ByteInst::_ISET_NA: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					
					ram[*dest + off + 0] = getNext();
					ram[*dest + off + 1] = getNext();
					ram[*dest + off + 2] = getNext();
					ram[*dest + off + 3] = getNext();
					
					break;
				}
				case ByteInst::_ISET_NS: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					
					ram[*dest - off + 0] = getNext();
					ram[*dest - off + 1] = getNext();
					ram[*dest - off + 2] = getNext();
					ram[*dest - off + 3] = getNext();
					
					break;
				}
				
				// WSET
				case ByteInst::_WSET_RA: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* src = getRegister(getNext());
					unsigned char* data = Util::wtoa((unsigned short)*src);
					
					ram[*dest + off + 0] = data[0];
					ram[*dest + off + 1] = data[1];
					
					break;
				}
				case ByteInst::_WSET_RS: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* src = getRegister(getNext());
					unsigned char* data = Util::wtoa((unsigned short)*src);
					
					ram[*dest - off + 0] = data[0];
					ram[*dest - off + 1] = data[1];
					
					break;
				}
				case ByteInst::_WSET_NA: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					
					ram[*dest + off + 0] = getNext();
					ram[*dest + off + 1] = getNext();
					
					break;
				}
				case ByteInst::_WSET_NS: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					
					ram[*dest - off + 0] = getNext();
					ram[*dest - off + 1] = getNext();
					
					break;
				}
				
				// BSET
				case ByteInst::_BSET_RA: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* src = getRegister(getNext());
					
					ram[*dest + off] = (unsigned char)*src;
					
					break;
				}
				case ByteInst::_BSET_RS: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					unsigned int* src = getRegister(getNext());
					
					ram[*dest - off] = (unsigned char)*src;
					
					break;
				}
				case ByteInst::_BSET_NA: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					
					ram[*dest + off] = getNext();
					
					break;
				}
				case ByteInst::_BSET_NS: {
					unsigned int* dest = getRegister(getNext());
					unsigned int off = Util::atoi(getNext(), getNext(), getNext(), getNext());
					
					ram[*dest - off] = getNext();
					
					break;
				}
				
				// FREE
				case ByteInst::_FREE: {
					unsigned int addr = popi();
					heap_free(addr);
					break;
				}
				
				// NCALL
				case ByteInst::_NCALL: {
					ncall();
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
	
	void Runtime::ncall() {
		char* pre = new char[256];
		char* func = new char[256];
		char c;

		// Get library name
		int x = 0;
		while ((c = getNext()) != '.')
			pre[x++] = c;
		pre[x] = 0;

		// Get function name
		x = 0;
		while ((c = getNext()) != '\0')
			func[x++] = c;
		func[x] = 0;

		pushi(this->pc);
		pushi(this->bp);
		this->bp = this->sp;

		// Call natively
		if (!strcmp(pre, "sys")) {
			this->erx = this->sys->callFunction(func);
		} else {
			int (*native)(char*, char*) = (int (*)(char*, char*))dlsym(sys->lib, "ncall");
			this->erx = native(pre, func);
		}
		
		// NativeLib* lib = NativeLib::getByName(libs, pre);
		// if (!lib) {
		// 	printf("ERR: Could not load native '%s'\n", pre);
		// 	exit(1);
		// }
		// this->erx = lib->callFunction(func);
		
		this->bp = popi();
		this->pc = popi();
		
		delete[] pre;
		delete[] func;
	}

	void Runtime::openl(int ptr) {
		// TODO: Nothing
	}

	void Runtime::addLibrary(NativeLib* lib) {
		lib->bind(this->env);		// Bind library
		//this->libs->add(lib);		// Add to list
	}

	void Runtime::heap_alloc(unsigned int size) {
		if (size == 0) {
			printf("ERR: Can not allocate zero bytes\n");
			exit(1);
		}
		
		if (HEAP_ROOT->next == nullptr) {
			HeapNode* h = new HeapNode(HEAP_ROOT, nullptr, HEAP_START, HEAP_START + size);
			HEAP_ROOT->next = h;
			pushi(h->begin);
		} else {
			HeapNode* h = HEAP_ROOT->next;
			while (h->next != nullptr) {
				if (h->next->begin - h->end >= size) {
					HeapNode* n = new HeapNode(h, h->next, h->end, h->end + size);
					h->next->last = n;	// Set child parent to new one
					h->next = n;		// Set child to new one
					pushi(n->begin);	// Push the malloc'd address
					return;
				}
				h = h->next;
			}
			// Being here means we haven't found enough space
			// So add onto the end
			HeapNode* n = new HeapNode(h, nullptr, h->end, h->end + size);
			h->next = n;
			pushi(n->begin);
		}
	}
	
	void Runtime::heap_free(unsigned int addr) {
		HeapNode* h = HEAP_ROOT;
		while (h->next != nullptr) {
			if (h->next->begin == addr) {
				delete h->next;
				return;
			}
			h = h->next;
		}
		printf("ERR: The address 0x%08X can not be freed!\n", addr);
		exit(1);
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
	
	void Runtime::pushb(unsigned char a) {
		ram[--sp] = a;
	}
	
	unsigned char Runtime::popb() {
		return ram[sp++];
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
			case _ERX:
				return &erx;
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
