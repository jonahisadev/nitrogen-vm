#ifndef NITROGEN_PARSER_H
#define NITROGEN_PARSER_H

#include <cstring>
#include <cstdlib>
#include <cstring>

#include <Nitrogen/Util.h>
#include <Nitrogen/List.h>
#include <Nitrogen/Token.h>
#include <Nitrogen/Compiler.h>
#include <Nitrogen/Type.h>

namespace Nitrogen {

	class Parser {
	private:
		char* source;
		
		List<Token*>* tokens;
		List<Label*>* labels;
		List<Var*>* vars;
		List<char*>* jumps;
		List<char*>* loads;
		
		List<char*>* strings;
		
		const char* entry = "start";
		
		int section = 0;
		
	public:
		Parser(char* src);
		~Parser();
		
		void start();
		void printTokens();
		void handlePreProc(char* str, int line);
		void handleAddress(char* str, int line);
		
		Compiler* createCompiler();
	};

}

#endif // NITROGEN_PARSER_H