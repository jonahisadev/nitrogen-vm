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
				
				// IADDR
				case _IADDR_RA: {
					printf("IADDR \t%s, (%s)", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					int x;
					if ((x = getNext()) != 0) {
						printf("+%d", x);
					}
					break;
				}
				case _IADDR_RS: {
					printf("IADDR \t%s, (%s)-%d", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()), getNext());
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
				
				// WADDR
				case _WADDR_RA: {
					printf("WADDR \t%s, (%s)", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()));
					int x;
					if ((x = getNext()) != 0) {
						printf("+%d", x);
					}
					break;
				}
				case _WADDR_RS: {
					printf("WADDR \t%s, (%s)-%d", Bytecode::getRegister(getNext()), Bytecode::getRegister(getNext()), getNext());
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
					printf("LDB \t\t%s, %08X", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// LDW
				case _LDW: {
					printf("LDW \t\t%s, %08X", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
					break;
				}
				
				// LDD
				case _LDD: {
					printf("LDD \t\t%s, %08X", Bytecode::getRegister(getNext()), Util::atoi(getNext(), getNext(), getNext(), getNext()));
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