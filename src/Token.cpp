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
				}
				printf("\n");
			}
			
			// NUM
			else if (t->getType() == NUM) {
				printf("NUM: %d\n", t->getData());
			}
		}
	}

}