#include <Nitrogen/Parser.h>

namespace Nitrogen {

	Parser::Parser(char* source) {
		this->source = strdup(source);
		this->tokens = new List<Token*>(1);
	}
	
	Parser::~Parser() {
		free(this->source);
		delete tokens;
	}
	
	void Parser::start() {
		char lex[256];
		int lexi = 0;
		int i = 0;
		int line = 1;
		
		resetLex:
		for (int x = 0; x < 256; x++)
			lex[x] = '\0';
		lexi = 0;
		
		while (source[i] != ' ') {
			if (source[i] == '\n' || source[i] == '\0')
				break;
				
			lex[lexi++] = source[i++];
		}
		
		// NUMBERS
		if (Util::isNumber(lex)) {
			tokens->add(new Token(NUM, Util::convertNum(lex, 10), line));
			goto end;
		}
		
		// INST
		else if (!strcmp(lex, "iconst")) {
			tokens->add(new Token(INST, ICONST, line));
			goto end;
		}
		
		end:
		if (source[i] == ' ') {
			i++;
			goto resetLex;
		}
		else if (source[i] == '\n') {
			i++;
			line++;
			goto resetLex;
		}
		else if (source[i] == '\0') {
			return;
		}
	}
	
	void Parser::printTokens() {
		Token::printTokenList(tokens);
	}
	
	Compiler* Parser::createCompiler() {
		Compiler* c = new Compiler();
		c->setTokens(this->tokens);
		return c;
	}

}