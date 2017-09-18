#ifndef NITROGEN_PARSER_H
#define NITROGEN_PARSER_H

#include <Nitrogen/Util.h>
#include <Nitrogen/List.h>
#include <Nitrogen/Token.h>

#include <cstring>
#include <cstdlib>
#include <cstring>

namespace Nitrogen {

	class Parser {
	private:
		char* source;
		
		List<Token*>* tokens;
		
	public:
		Parser(char* src);
		~Parser();
		
		void start();
		void printTokens();
	};

}

#endif // NITROGEN_PARSER_H