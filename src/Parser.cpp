#include <Nitrogen/Parser.h>

namespace Nitrogen {

	Parser::Parser(char* path) {
		this->path = path;
		this->source = strdup(Util::readFile(path));
		
		this->tokens = new List<Token*>(1);
		this->labels = new List<Label*>(1);
		this->vars = new List<Var*>(1);
		this->jumps = new List<char*>(1);
		this->loads = new List<char*>(1);
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
			
			// Strings
			else if (source[i] == '"') {
				delim = '"';
			}
			
			lex[lexi++] = source[i++];
		}
		
		if (delim == '"') {
			delim = ' ';
			lex[lexi++] = '"';
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
		
		// HEX
		else if (Util::isHex(lex)) {
			char* str = Util::strDupX(lex, 2, strlen(lex));
			tokens->add(new Token(NUM, Util::convertNum(str, 16), line));
			goto end;
		}
		
		// LABELS
		else if (lex[strlen(lex)-1] == ':') {
			if (this->section == SEC_TEXT) {
				labels->add(new Label(Util::strDupX(lex, 0, strlen(lex)-1), 0));
				tokens->add(new Token(LABEL, labels->getSize()-1, line));
			}
			else if (this->section == SEC_DATA) {
				vars->add(new Var(Util::strDupX(lex, 0, strlen(lex)-1), 0));
				tokens->add(new Token(VAR, vars->getSize()-1, line));
			}
			else {
				printf("ERR: (%s:%d) No section defined. Symbols can not be created\n", path, line);
				exit(1);
			}
			goto end;
		}
		
		// JUMP
		else if (lex[0] == '@') {
			jumps->add(Util::strDupX(lex, 1, strlen(lex)));
			tokens->add(new Token(JUMP, jumps->getSize()-1, line));
			goto end;
		}
		
		// LOAD
		else if (lex[0] == '$') {
			loads->add(Util::strDupX(lex, 1, strlen(lex)));
			tokens->add(new Token(LOAD, loads->getSize()-1, line));
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

		// STRINGS
		else if (lex[0] == '"' && lex[strlen(lex)-1] == '"') {
			char *str = Util::strDupX(lex, 1, strlen(lex) - 1);
			// printf("Found a string '%s'!\n", str);
			strings->add(str);
			tokens->add(new Token(STRING, strings->getSize()-1, line));
			i++;
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
			printf("ERR: (%s:%d) Invalid token: '%s'\n", path, line, lex);
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
		c->setVars(this->vars);
		c->setJumps(this->jumps);
		c->setLoads(this->loads);
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
		
		// INCLUDE
		if (!strcmp(lex, "#include")) {
			// Get path
			char* path = new char[256];
			i += 2;
			int x = 0;
			while (str[i] != '"') {
				path[x++] = str[i++];
			}
			path[x] = '\0';

			include(this, path);
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
		
		// SECTION
		else if (!strcmp(lex, "#section")) {
			char* type = new char[strlen(str) - 9];
			int z = 0;
			for (int x = 9; x < strlen(str); x++) {
				type[z++] = str[x];
			}
			type[z] = '\0';
			if (!strcmp(type, "TEXT")) {
				tokens->add(new Token(PREPROC, SEC_TEXT, line));
				this->section = SEC_TEXT;
			} else if (!strcmp(type, "DATA")) {
				tokens->add(new Token(PREPROC, SEC_DATA, line));
				this->section = SEC_DATA;
			} else {
				printf("ERR: (%s:%d) Invalid section '%s'\n", path, line, type);
				exit(1);
			}
		}
		
		// WHO KNOWS
		else {
			printf("ERR: (%s:%d) Invalid preprocessor '%s'\n", path, line, str);
			exit(1);
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
		} else if (!strcmp(lex, "eax")) {
			tokens->add(new Token(TokenType::REG, EAX, line));
		} else if (!strcmp(lex, "ebx")) {
			tokens->add(new Token(TokenType::REG, EBX, line));
		} else if (!strcmp(lex, "ecx")) {
			tokens->add(new Token(TokenType::REG, ECX, line));
		} else if (!strcmp(lex, "edx")) {
			tokens->add(new Token(TokenType::REG, EDX, line));
		} else if (!strcmp(lex, "erx")) {
			tokens->add(new Token(TokenType::REG, ERX, line));
		}
		else {
			printf("ERR: (%s:%d) Invalid address! '%s'\n", path, line, lex);
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
			
			int num;
			if (Util::isNumber(lex)) {
				num = Util::convertNum(lex, 10);
			} else if (Util::isHex(lex)) {
				char* str = Util::strDupX(lex, 2, strlen(lex));
				num = Util::convertNum(lex, 16);
				delete str;
			} else {
				printf("ERR: (%s:%d) Must offset address by a number\n", path, line);
				exit(1);
			}
			if (c == '+') {
				tokens->add(new Token(NUM, num, line));
			} else if (c == '-') {
				tokens->add(new Token(NUM, -num, line));
			}
		} else {
			tokens->add(new Token(NUM, 0, line));
		}
	}

	void Parser::include(Parser* p, char* path) {
		// Run parser
		Parser* sub = new Parser(path);
		sub->start();
	
		// Save Sizes
		int tSize = sub->tokens->getSize();
		int lblSize = sub->labels->getSize();
		int vSize = sub->vars->getSize();
		int jSize = sub->jumps->getSize();
		int ldSize = sub->loads->getSize();
		int strSize = sub->strings->getSize();

		// Append data
		tokens->append(sub->tokens);
		labels->append(sub->labels);
		vars->append(sub->vars);
		jumps->append(sub->jumps);
		loads->append(sub->loads);
		strings->append(sub->strings);

		// Adjust pointers
		for (int i = tSize - 1; i < tokens->getSize(); i++) {
			Token* t = tokens->get(i);
			switch (t->getType()) {
				case LABEL:
					t->setData(t->getData() + lblSize); break;
				case JMP:
					t->setData(t->getData() + jSize); break;
				case LOAD:
					t->setData(t->getData() + ldSize); break;
				case VAR:
					t->setData(t->getData() + vSize); break;
				case STRING:
					t->setData(t->getData() + strSize); break;
			}
		}

		// Clean up
		delete sub;
	}

}