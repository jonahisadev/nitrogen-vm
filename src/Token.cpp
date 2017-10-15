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
		if (!strcmp(str, "ICONST"))
			return ICONST;
		else if (!strcmp(str, "ILOAD"))
			return ILOAD;
		else if (!strcmp(str, "ISTORE"))
			return ISTORE;
		else if (!strcmp(str, "IMOV"))
			return IMOV;
		else if (!strcmp(str, "IADD"))
			return IADD;
		else if (!strcmp(str, "ISUB"))
			return ISUB;
		else if (!strcmp(str, "IMUL"))
			return IMUL;
		else if (!strcmp(str, "IDIV"))
			return IDIV;
		else if (!strcmp(str, "IADDR"))
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