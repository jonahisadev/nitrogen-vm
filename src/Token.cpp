#include <Nitrogen/Token.h>

namespace Nitrogen {

	Token::Token(int type, int data, int line) {
		this->type = type;
		this->data = data;
		this->line = line;
	}
	
	Token::~Token() {
		// Nothing
	}
	
	int Token::isInstruction(char* str) {
		Util::toUpper(str);
		if (!strcmp(str, "ICONST") || !strcmp(str, "CONST"))
			return ICONST;
		else if (!strcmp(str, "ILOAD") || !strcmp(str, "LOAD"))
			return ILOAD;
		else if (!strcmp(str, "ISTORE") || !strcmp(str, "STORE"))
			return ISTORE;
		else if (!strcmp(str, "IMOV") || !strcmp(str, "MOV"))
			return IMOV;
		else if (!strcmp(str, "IADD") || !strcmp(str, "ADD"))
			return IADD;
		else if (!strcmp(str, "ISUB") || !strcmp(str, "SUB"))
			return ISUB;
		else if (!strcmp(str, "IMUL") || !strcmp(str, "MUL"))
			return IMUL;
		else if (!strcmp(str, "IDIV") || !strcmp(str, "DIV"))
			return IDIV;
		else if (!strcmp(str, "IADDR") || !strcmp(str, "ADDR"))
			return IADDR;
			
		else if (!strcmp(str, "WCONST"))
			return WCONST;
		else if (!strcmp(str, "WLOAD"))
			return WLOAD;
		else if (!strcmp(str, "WSTORE"))
			return WSTORE;
		else if (!strcmp(str, "WMOV"))
			return WMOV;
		else if (!strcmp(str, "WADD"))
			return WADD;
		else if (!strcmp(str, "WSUB"))
			return WSUB;
		else if (!strcmp(str, "WMUL"))
			return WMUL;
		else if (!strcmp(str, "WDIV"))
			return WDIV;
		else if (!strcmp(str, "WADDR"))
			return WADDR;
			
		else if (!strcmp(str, "BCONST"))
			return BCONST;
		else if (!strcmp(str, "BLOAD"))
			return BLOAD;
		else if (!strcmp(str, "BSTORE"))
			return BSTORE;
		else if (!strcmp(str, "BMOV"))
			return BMOV;
		else if (!strcmp(str, "BADD"))
			return BADD;
		else if (!strcmp(str, "BSUB"))
			return BSUB;
		else if (!strcmp(str, "BMUL"))
			return BMUL;
		else if (!strcmp(str, "BDIV"))
			return BDIV;
		else if (!strcmp(str, "BADDR"))
			return BADDR;
			
		else if (!strcmp(str, "DB"))
			return DB;
		else if (!strcmp(str, "DW"))
			return DW;
		else if (!strcmp(str, "DD"))
			return DD;	
		else if (!strcmp(str, "LDB"))
			return LDB;
		else if (!strcmp(str, "LDW"))
			return LDW;
		else if (!strcmp(str, "LDD"))
			return LDD;
		else if (!strcmp(str, "STB"))
			return STB;
		else if (!strcmp(str, "STW"))
			return STW;
		else if (!strcmp(str, "STD"))
			return STD;
		
		else if (!strcmp(str, "JMP"))
			return JMP;
		else if (!strcmp(str, "CALL"))
			return CALL;
		else if (!strcmp(str, "RET"))
			return RET;
		else if (!strcmp(str, "INC"))
			return INC;
		else if (!strcmp(str, "DEC"))
			return DEC;
		else if (!strcmp(str, "NCALL"))
			return NCALL;
			
		else if (!strcmp(str, "PUSHA"))
			return PUSHA;
		else if (!strcmp(str, "POPA"))
			return POPA;
			
		else if (!strcmp(str, "CMP"))
			return CMP;
		else if (!strcmp(str, "JL"))
			return JL;
		else if (!strcmp(str, "JG"))
			return JG;
		else if (!strcmp(str, "JLE"))
			return JLE;
		else if (!strcmp(str, "JGE"))
			return JGE;
		else if (!strcmp(str, "JE"))
			return JE;
		else if (!strcmp(str, "JNE"))
			return JNE;
			
		else if (!strcmp(str, "EXIT"))
			return EXIT;
		else
			return -1;
	}
	
	int Token::isRegister(char* str) {
		Util::toUpper(str);
		if (!strcmp(str, "EAX"))
			return EAX;
		else if (!strcmp(str, "EBX"))
			return EBX;
		else if (!strcmp(str, "ECX"))
			return ECX;
		else if (!strcmp(str, "EDX"))
			return EDX;
		else if (!strcmp(str, "ERM"))
			return ERM;
		else if (!strcmp(str, "ERX"))
			return ERX;
		else if (!strcmp(str, "ESP"))
			return ESP;
		else if (!strcmp(str, "EBP"))
			return EBP;
		else
			return -1;
	}
	
	void Token::printTokenList(List<Token*>* tokens) {
		Token* t;
		printf("Printing %d tokens...\n", tokens->getSize());
		
		for (int i = 0; i < tokens->getSize(); i++) {
			t = tokens->get(i);
			printf("(%d) ", t->getLine());
			
			// INST
			if (t->getType() == INST) {
				printf("INST: ");
				switch (t->getData()) {
					case ICONST:
						printf("ICONST"); break;
					case ILOAD:
						printf("ILOAD"); break;
					case ISTORE:
						printf("ISTORE"); break;
					case IMOV:
						printf("IMOV"); break;
					case IADD:
						printf("IADD"); break;
					case ISUB:
						printf("ISUB"); break;
					case IMUL:
						printf("IMUL"); break;
					
					case IADDR:
						printf("IADDR"); break;
					
					case JMP:
						printf("JMP"); break;
					case CALL:
						printf("CALL"); break;
					case RET:
						printf("RET"); break;
						
					case NCALL:
						printf("NCALL"); break;
				}
				printf("\n");
			}
			
			//REG
			else if (t->getType() == REG) {
				printf("REG: ");
				switch (t->getData()) {
					case EAX:
						printf("EAX"); break;
					case EBX:
						printf("EBX"); break;
					case ECX:
						printf("ECX"); break;
					case EDX:
						printf("EDX"); break;
					case ERX:
						printf("ERX"); break;
					case ESP:
						printf("ESP"); break;
					case EBP:
						printf("EBP"); break;
				}
				printf("\n");
			}
			
			// NUM
			else if (t->getType() == NUM) {
				printf("NUM: %d\n", t->getData());
			}
			
			// JUMP/LABEL
			else if (t->getType() == LABEL) {
				printf("LABEL: %d\n", t->getData());
			}
			else if (t->getType() == JUMP) {
				printf("JUMP: %d\n", t->getData());
			}
		}
	}

}