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
		if (prog[0] == 'N' && prog[1] == '7') {
			printf(":Nitrogen Binary\n");
			pc += 2;
		} else {
			printf("Invalid Nitrogen Binary\n");
			exit(1);
		}
		
		int opcode;
		while (this->pc < this->bin_size) {
			opcode = prog[pc];
			
			printf("%08X: ", pc);
			switch (opcode) {
				// NOP
				case _NOP: {
					printf("NOP");
					break;
				}
				
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
				
				// IADD
				case _IADD_R: {
					printf("IADD \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _IADD_N: {
					printf("IADD \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// ISUB
				case _ISUB_R: {
					printf("ISUB \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _ISUB_N: {
					printf("ISUB \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// IMUL
				case _IMUL_R: {
					printf("IMUL \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _IMUL_N: {
					printf("IMUL \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// IDIV
				case _IDIV_R: {
					printf("IDIV \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _IDIV_N: {
					printf("IDIV \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// WCONST
				case _WCONST: {
					printf("WCONST \t%d", Util::atow(getNext(), getNext()));
					break;
				}
				
				// WLOAD
				case _WLOAD: {
					printf("WLOAD \t%s", Bytecode::getRegister(getNext()));
					break;
				}
				
				// WSTORE
				case _WSTORE: {
					printf("WSTORE \t%s", Bytecode::getRegister(getNext()));
					break;
				}
				
				// WMOV
				case _WMOV_R: {
					printf("WMOV \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _WMOV_N: {
					printf("WMOV \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atow(getNext(), getNext()));
					break;
				}
				
				// WADD
				case _WADD_R: {
					printf("WADD \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _WADD_N: {
					printf("WADD \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atow(getNext(), getNext()));
					break;
				}
				
				// WSUB
				case _WSUB_R: {
					printf("WSUB \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _WSUB_N: {
					printf("WSUB \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atow(getNext(), getNext()));
					break;
				}
				
				// WMUL
				case _WMUL_R: {
					printf("WMUL \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _WMUL_N: {
					printf("WMUL \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atow(getNext(), getNext()));
					break;
				}
				
				// WDIV
				case _WDIV_R: {
					printf("WDIV \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _WDIV_N: {
					printf("WDIV \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atow(getNext(), getNext()));
					break;
				}
				
				// BCONST
				case _BCONST: {
					printf("BCONST \t%d", getNext());
					break;
				}
				
				// BLOAD
				case _BLOAD: {
					printf("BLOAD \t%s", Bytecode::getRegister(getNext()));
					break;
				}
				
				// WSTORE
				case _BSTORE: {
					printf("BSTORE \t%s", Bytecode::getRegister(getNext()));
					break;
				}
				
				// BMOV
				case _BMOV_R: {
					printf("BMOV \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _BMOV_N: {
					printf("BMOV \t\t%s, %d", Bytecode::getRegister(getNext()), getNext());
					break;
				}
				
				// BADD
				case _BADD_R: {
					printf("BADD \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _BADD_N: {
					printf("BADD \t\t%s, %d", Bytecode::getRegister(getNext()), getNext());
					break;
				}
				
				// BSUB
				case _BSUB_R: {
					printf("BSUB \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _BSUB_N: {
					printf("BSUB \t\t%s, %d", Bytecode::getRegister(getNext()), getNext());
					break;
				}
				
				// BMUL
				case _BMUL_R: {
					printf("BMUL \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _BMUL_N: {
					printf("BMUL \t\t%s, %d", Bytecode::getRegister(getNext()), getNext());
					break;
				}
				
				// BDIV
				case _BDIV_R: {
					printf("BDIV \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _BDIV_N: {
					printf("BDIV \t\t%s, %d", Bytecode::getRegister(getNext()), getNext());
					break;
				}
				
				// DB
				case _DB: {
					printf("DB \t\t%d", getNext());
					break;
				}
				
				// DW
				case _DW: {
					printf("DW \t\t%d", Util::atow(getNext(), getNext()));
					break;
				}
				
				// DD
				case _DD: {
					printf("DD \t\t%d", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// LDB
				case _LDB: {
					printf("LDB \t\t%s, 0x%08X", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// LDW
				case _LDW: {
					printf("LDW \t\t%s, 0x%08X", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// LDD
				case _LDD: {
					printf("LDD \t\t%s, 0x%08X", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// STB
				case _STB_VR: {
					printf("STB \t\t0x%08X, %s", Util::atoi(getNext(), getNext(), getNext(), getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _STB_VN: {
					printf("STB \t\t0x%08X, %d", Util::atoi(getNext(), getNext(), getNext(), getNext()), getNext());
					break;
				}
				
				// STW
				case _STW_VR: {
					printf("STW \t\t0x%08X, %s", Util::atoi(getNext(), getNext(), getNext(), getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _STW_VN: {
					printf("STW \t\t0x%08X, %d", Util::atoi(getNext(), getNext(), getNext(), getNext()), Util::atow(getNext(), getNext()));
					break;
				}
				
				// STD
				case _STD_VR: {
					printf("STD \t\t0x%08X, %s", Util::atoi(getNext(), getNext(), getNext(), getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _STD_VN: {
					printf("STD \t\t0x%08X, %d", Util::atoi(getNext(), getNext(), getNext(), getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// JMP
				case _JMP: {
					printf("JMP \t\t0x%08X", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// CALL
				case _CALL: {
					printf("CALL \t\t0x%08X", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// RET
				case _RET: {
					printf("RET");
					break;
				}
				
				// INC
				case _INC: {
					printf("INC \t\t%s", Bytecode::getRegister(getNext()));
					break;
				}
				
				// DEC
				case _DEC: {
					printf("DEC \t\t%s", Bytecode::getRegister(getNext()));
					break;
				}
				
				// PUSHA
				case _PUSHA: {
					printf("PUSHA");
					break;
				}
				
				// POPA
				case _POPA: {
					printf("POPA");
					break;
				}
				
				// HINIT
				case _HINIT: {
					printf("HINIT");
					break;
				}
				
				// MALLOC
				case _MALLOC_R: {
					printf("MALLOC \t%s", Bytecode::getRegister(getNext()));
					break;
				}
				case _MALLOC_N: {
					printf("MALLOC \t%d", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// IGET
				case _IGET_A: {
					printf("IGET \t\t%s, (%s)", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					break;
				}
				case _IGET_S: {
					printf("IGET \t\t%s, (%s)-%d", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// WGET
				case _WGET_A: {
					printf("WGET \t\t%s, (%s)", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					break;
				}
				case _WGET_S: {
					printf("WGET \t\t%s, (%s)-%d", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// BGET
				case _BGET_A: {
					printf("BGET \t\t%s, (%s)", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					break;
				}
				case _BGET_S: {
					printf("BGET \t\t%s, (%s)-%d", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// ISET
				case _ISET_RA: {
					printf("ISET \t\t(%s)", Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					printf(", %s", Bytecode::getRegister(getNext()));
					break;
				}
				case _ISET_RS: {
					printf("ISET \t\t(%s)-%d, %s", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _ISET_NA: {
					printf("ISET \t\t(%s)", Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					printf(", %d", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				case _ISET_NS: {
					printf("ISET \t\t(%s)-%d, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// WSET
				case _WSET_RA: {
					printf("WSET \t\t(%s)", Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					printf(", %s", Bytecode::getRegister(getNext()));
					break;
				}
				case _WSET_RS: {
					printf("WSET \t\t(%s)-%d, %s", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _WSET_NA: {
					printf("WSET \t\t(%s)", Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					printf(", %d", Util::atow(getNext(), getNext()));
					break;
				}
				case _WSET_NS: {
					printf("WSET \t\t(%s)-%d, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()), Util::atow(getNext(), getNext()));
					break;
				}
				
				// BSET
				case _BSET_RA: {
					printf("BSET \t\t(%s)", Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					printf(", %s", Bytecode::getRegister(getNext()));
					break;
				}
				case _BSET_RS: {
					printf("BSET \t\t(%s)-%d, %s", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _BSET_NA: {
					printf("BSET \t\t(%s)", Bytecode::getRegister(getNext()));
					int x;
					if ((x = Util::atoi(getNext(), getNext(), getNext(), getNext())) != 0) {
						printf("+%d", x);
					}
					printf(", %d", getNext());
					break;
				}
				case _BSET_NS: {
					printf("BSET \t\t(%s)-%d, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()), getNext());
					break;
				}
				
				// FREE
				case _FREE: {
					printf("FREE");
					break;
				}
				
				// NCALL
				case _NCALL: {
					printf("NCALL \t");
					char c;
					while ((c = getNext()) != '\0') {
						printf("%c", c);
					}
					break;
				}
				
				// CMP
				case _CMP_R: {
					printf("CMP \t\t%s, %s", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					break;
				}
				case _CMP_N: {
					printf("CMP \t\t%s, %d", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// BRANCHES
				case _JL: {
					printf("JL \t\t0x%08X", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				case _JG: {
					printf("JG \t\t0x%08X", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				case _JLE: {
					printf("JLE \t\t0x%08X", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				case _JGE: {
					printf("JGE \t\t0x%08X", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				case _JE: {
					printf("JE \t\t0x%08X", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				case _JNE: {
					printf("JNE \t\t0x%08X", Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// EXIT
				case _EXIT: {
					printf("EXIT");
					break;
				}
				
				default:
					printf("???\n"); break;
			}
			printf("\n");
			
			pc++;
		}
	}

	unsigned char Decomp::getNext() {
		return prog[++pc];
	}

}