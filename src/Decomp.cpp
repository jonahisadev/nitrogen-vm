#include <Nitrogen/Decomp.h>

namespace Nitrogen {

	Decomp::Decomp(unsigned char* prog, int len) {
		this->prog = prog;
		this->bin_size = len;

		this->labels = new List<Symbol*>(1);
		this->vars = new List<Symbol*>(1);
	}
	
	Decomp::~Decomp() {
		delete[] this->prog;
	}

	void Decomp::loadSymbols() {
		FILE* file = fopen(".symdat", "rb");
		if (!file) {
			printf("****** No symbols located! ******\n");
			return;
		}

		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		fseek(file, 0, SEEK_SET);

		char* buf = new char[size];
		fread(buf, 1, size, file);
		fclose(file);

		int i = 0;

		int lsize = Util::atoi(buf[i], buf[i+1], buf[i+2], buf[i+3]); i += 4;
		int vsize = Util::atoi(buf[i], buf[i + 1], buf[i + 2], buf[i + 3]); i += 4;

		// TODO: Make this system a lot better

		int x = 0;
		while (x < lsize) {
			unsigned int addr = Util::atoi(buf[i], buf[i + 1], buf[i + 2], buf[i + 3]);
			i += 4;
			char* str = new char[256];
			char c;
			int j = 0;
			while ((c = buf[i++]) != 0) {
				str[j++] = c;
			}
			// printf("label: %s, \t0x%08X\n", str, addr);
			labels->add(new Symbol(str, addr));
			x++;
			delete[] str;
		}

		x = 0;
		while (x < vsize) {
			unsigned int addr = Util::atoi(buf[i], buf[i + 1], buf[i + 2], buf[i + 3]);
			i += 4;
			char *str = new char[256];
			char c;
			int j = 0;
			while ((c = buf[i++]) != 0)
			{
				str[j++] = c;
			}
			// printf("variable: %s, \t0x%08X\n", str, addr);
			vars->add(new Symbol(str, addr));
			x++;
			delete[] str;
		}
	}

	void Decomp::printLabel(unsigned int addr) {
		for (int i = 0; i < labels->getSize(); i++) {
			if (labels->get(i)->addr == addr) {
				printf("\t\t(%s)", labels->get(i)->name);
				break;
			}
		}
	}

	void Decomp::printVar(unsigned int addr) {
		for (int i = 0; i < vars->getSize(); i++) {
			if (vars->get(i)->addr == addr) {
				printf("\t\t($%s)", vars->get(i)->name);
				break;
			}
		}
	}

	void Decomp::start() {
		loadSymbols();

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
			
			// Print labels as they come
			for (int i = 0; i < labels->getSize(); i++) {
				if (labels->get(i)->addr == pc) {
					printf("\n%s:\n", labels->get(i)->name);
				}
			}

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

				// DS
				case _DS: {
					printf("DS \t\t\"");
					char c;
					while ((c = getNext()) != '\0') {
						printf("%c", c);
					}
					printf("\"");
					break;
				}
				
				// LDB
				case _LDB: {
					printf("LDB \t\t%s, ", Bytecode::getRegister(getNext()));
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("0x%08X", addr);
					printVar(addr);
					break;
				}
				
				// LDW
				case _LDW: {
					printf("LDW \t\t%s, ", Bytecode::getRegister(getNext()));
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("0x%08X", addr);
					printVar(addr);
					break;
				}
				
				// LDD
				case _LDD: {
					printf("LDD \t\t%s, ", Bytecode::getRegister(getNext()));
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("0x%08X", addr);
					printVar(addr);
					break;
				}

				// LDS
				case _LDS: {
					printf("LDS \t\t%s, ", Bytecode::getRegister(getNext()));
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("0x%08X", addr);
					printVar(addr);
					break;
				}
				
				// STB
				case _STB_VR: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("STB \t\t0x%08X, %s", addr, Bytecode::getRegister(getNext()));
					printVar(addr);
					break;
				}
				case _STB_VN: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("STB \t\t0x%08X, %d", addr, getNext());
					printVar(addr);
					break;
				}
				
				// STW
				case _STW_VR: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("STW \t\t0x%08X, %s", addr, Bytecode::getRegister(getNext()));
					printVar(addr);
					break;
				}
				case _STW_VN: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("STW \t\t0x%08X, %d", addr, Util::atow(getNext(), getNext()));
					printVar(addr);
					break;
				}
				
				// STD
				case _STD_VR: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("STD \t\t0x%08X, %s", addr, Bytecode::getRegister(getNext()));
					printVar(addr);
					break;
				}
				case _STD_VN: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("STD \t\t0x%08X, %d", addr, Util::atoi(getNext(), getNext(), getNext(), getNext()));
					printVar(addr);
					break;
				}
				
				// JMP
				case _JMP: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("JMP \t\t0x%08X", addr);
					printLabel(addr);
					break;
				}
				
				// CALL
				case _CALL: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("CALL \t\t0x%08X", addr);
					printLabel(addr);
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
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("JL \t\t0x%08X", addr);
					printLabel(addr);
					break;
				}
				case _JG: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("JG \t\t0x%08X", addr);
					printLabel(addr);
					break;
				}
				case _JLE: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("JLE \t\t0x%08X", addr);
					printLabel(addr);
					break;
				}
				case _JGE: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("JGE \t\t0x%08X", addr);
					printLabel(addr);
					break;
				}
				case _JE: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("JE \t\t0x%08X", addr);
					printLabel(addr);
					break;
				}
				case _JNE: {
					unsigned int addr = Util::atoi(getNext(), getNext(), getNext(), getNext());
					printf("JNE \t\t0x%08X", addr);
					printLabel(addr);
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