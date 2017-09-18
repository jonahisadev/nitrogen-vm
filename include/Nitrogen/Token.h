#ifndef NITROGEN_TOKEN_H
#define NITROGEN_TOKEN_H

#include <cstdio>

#include <Nitrogen/List.h>

namespace Nitrogen {

	enum TokenType {
		INST,
		NUM
	};
	
	enum TokenInst {
		ICONST
	};

	class Token;
	template class List<Token*>;

	class Token {
	private:
		int type;
		int data;
		int line;
		
	public:
		Token(int type, int data, int line);
		~Token();
		
		static void printTokenList(List<Token*>* tokens);
		
		int getType() const { return type; }
		int getData() const { return data; }
		int getLine() const { return line; }
	};

}

#endif // NITROGEN_TOKEN_H