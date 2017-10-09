#ifndef NITROGEN_TOKEN_H
#define NITROGEN_TOKEN_H

#include <cstdio>

#include <Nitrogen/List.h>
#include <Nitrogen/Util.h>

namespace Nitrogen {

	enum TokenType {
		INST,
		NUM,
		REG,
		LABEL,
		JUMP,
		PREPROC,
	};
	
	enum TokenInst {
		ICONST,
		ILOAD,
		ISTORE,
		IMOV,
		
		JMP,
		CALL,
		RET,
		
		NCALL,
	};
	
	enum TokenReg {
		EAX,
		EBX,
		ECX,
		EDX,
		ESP,
		EBP
	};
	
	enum TokenPreProc {
		LIB_LOAD,
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
		
		static int isInstruction(char* str);
		static int isRegister(char* str);
		
		int getType() const { return type; }
		int getData() const { return data; }
		int getLine() const { return line; }
		
		void setData(int data) { this->data = data; }
	};

}

#endif // NITROGEN_TOKEN_H