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
	
	void Token::printTokenList(List<Token*>* tokens) {
		Token* t;
		printf("Printing %d tokens...\n", tokens->getSize());
		
		for (int i = 0; i < tokens->getSize(); i++) {
			t = tokens->get(i);
			
			if (t->getType() == INST) {
				printf("INST: ");
				switch (t->getData()) {
					case ICONST: {
						printf("ICONST"); break;
					}
				}
				printf("\n");
			}
			
			else if (t->getType() == NUM) {
				printf("NUM: %d\n", t->getData());
			}
		}
	}

}