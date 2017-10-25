#include <Nitrogen/Parser.h>

namespace Nitrogen {

	Parser::Parser(char* source) {
		this->source = strdup(source);
		
		this->tokens = new List<Token*>(1);
		this->labels = new List<Label*>(1);
		this->jumps = new List<char*>(1);
		this->strings = new List<char*>(1);
	}
	
	Parser::~Parser() {
		free(this->source);
		delete tokens;
	}
	
	void Parser::start() {
		char* lex = new char[256];
		int lexi = 0;
		int i = 0;
		int line = 1;
		char delim = ' ';
		
		resetLex:
		for (int x = 0; x < 256; x++)
			lex[x] = '\0';
		lexi = 0;
		
		while (source[i] != delim) {
			// Preprocessors
			if (source[i] == '#' && lexi == 0) {
				while (source[i] != '\n' && source[i] != '\0') {
					lex[lexi++] = source[i++];
				}
				lex[lexi] = '\0';
				handlePreProc(lex, line);
				goto resetLex;
			}
			
			// End of something
			if (source[i] == '\n' || source[i] == '\0')
				break;
			else if (source[i] == '\t') {
				i++;
				continue;
			}
			
			// Comments
			else if (source[i] == ';') {
				while (source[i] != '\n' && source[i] != '\0')
					i++;
				break;
			}
			
			else if (source[i] == '"') {
				delim = '"';
			}
			
			lex[lexi++] = source[i++];
		}
		
		if (delim == '"') {
			delim = ' ';
		}
		
		int token;
		
		// Ignore empty lines
		if (lex[0] == '\0')
			goto end;
		
		// NUMBERS
		if (Util::isNumber(lex)) {
			tokens->add(new Token(NUM, Util::convertNum(lex, 10), line));
			goto end;
		}
		
		// LABELS
		else if (lex[strlen(lex)-1] == ':') {
			labels->add(new Label(Util::strDupX(lex, 0, strlen(lex)-1), 0));
			tokens->add(new Token(LABEL, labels->getSize()-1, line));
			goto end;
		}
		
		// JUMP
		else if (lex[0] == '@') {
			jumps->add(Util::strDupX(lex, 1, strlen(lex)));
			tokens->add(new Token(JUMP, jumps->getSize()-1, line));
			goto end;
		}
		
		// NATIVE
		else if (lex[0] == '%') {
			strings->add(Util::strDupX(lex, 1, strlen(lex)));
			tokens->add(new Token(JUMP, strings->getSize()-1, line));
			goto end;
		}
		
		// ADDRESSES
		else if (lex[0] == '(') {
			handleAddress(lex, line);
			goto end;
		}
		
		// REGISTER
		else if ((token = Token::isRegister(lex)) != -1) {
			tokens->add(new Token(REG, token, line));
			goto end;
		}
		
		// INST
		else if ((token = Token::isInstruction(lex)) != -1) {
			tokens->add(new Token(INST, token, line));
			goto end;
		}
		
		else {
			printf("%d: Invalid token: '%s'\n", line, lex);
			exit(1);
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
		c->setLabels(this->labels);
		c->setJumps(this->jumps);
		c->setStrings(this->strings);
		c->setEntry(this->entry);
		return c;
	}
	
	void Parser::handlePreProc(char* str, int line) {
		char* lex = new char[256];
		int lexi = 0;
		int i = 0;
		
		while (str[i] != ' ') {
			if (str[i] == '\0')
				goto end;
			
			lex[lexi++] = str[i++];
		}
		
		// LOAD
		// TODO: VERY BROKEN!!!
		if (!strcmp(lex, "#load")) {
			char* path = new char[strlen(str) - 5];
			int z = 0;
			for (int x = 5; i < strlen(str); i++) {
				path[z++] = str[x];
			}
			path[z] = '\0';
			strings->add(path);
			tokens->add(new Token(LIB_LOAD, strings->getSize()-1, line));
		}
		
		// ENTRY
		else if (!strcmp(lex, "#entry")) {
			char* label = new char[strlen(str) - 7];
			int z = 0;
			for (int x = 7; x < strlen(str); x++) {
				label[z++] = str[x];
			}
			label[z] = '\0';
			this->entry = strdup(label);
		}
		
		end:
		return;
	}
	
	void Parser::handleAddress(char* str, int line) {
		enum AddrMode {
			REG
		};
		
		char* lex = new char[256];
		int lexi = 0;
		int i = 1;
		
		while (str[i] != ')') {
			lex[lexi++] = str[i++];
		}
		
		if (!strcmp(lex, "ebp")) {
			tokens->add(new Token(TokenType::REG, EBP, line));
		} else if (!strcmp(lex, "esp")) {
			tokens->add(new Token(TokenType::REG, ESP, line));
		} else {
			printf("%d: Invalid address! '%s'\n", line, lex);
		}
		
		i++;
		if (str[i] == '+' || str[i] == '-') {
			char c = str[i++];
			for (int x = 0; x < 256; x++)
				lex[x] = '\0';
			lexi = 0;
			
			while (str[i] != '\0') {
				lex[lexi++] = str[i++];
			}
			
			int num = Util::convertNum(lex, 10);
			if (c == '+') {
				tokens->add(new Token(NUM, num, line));
			} else if (c == '-') {
				tokens->add(new Token(NUM, -num, line));
			}
		} else {
			tokens->add(new Token(NUM, 0, line));
		}
	}

}