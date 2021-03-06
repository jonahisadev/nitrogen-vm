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
		VAR,
		JUMP,
		LOAD,
		PREPROC,
		STRING,
	};
	
	enum TokenInst {
		ICONST,
		ILOAD,
		ISTORE,
		IMOV,
		IADD,
		ISUB,
		IMUL,
		IDIV,
		
		WCONST,
		WLOAD,
		WSTORE,
		WMOV,
		WADD,
		WSUB,
		WMUL,
		WDIV,
		
		BCONST,
		BLOAD,
		BSTORE,
		BMOV,
		BADD,
		BSUB,
		BMUL,
		BDIV,
		
		DB,
		DW,
		DD,
		DS,
		LDB,
		LDW,
		LDD,
		LDS,
		STB,
		STW,
		STD,
		
		CALL,
		RET,
		NCALL,
		
		INC,
		DEC,
		
		PUSHA,
		POPA,
		
		MALLOC,
		FREE,
		IGET,
		WGET,
		BGET,
		ISET,
		WSET,
		BSET,
		
		JMP,
		JL,			// 0001
		JG,			// 0010
		JLE,		// 0101
		JGE,		// 0110
		JE,			// 0100
		JNE,		// x0xx
		CMP,
		
		EXIT
	};
	
	enum TokenReg {
		EAX,
		EBX,
		ECX,
		EDX,
		ERM,
		ERX,
		ESP,
		EBP
	};
	
	enum TokenPreProc {
		LIB_LOAD,
		SEC_TEXT,
		SEC_DATA,
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