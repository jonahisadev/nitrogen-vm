#ifndef NITROGEN_COMPILER_H
#define NITROGEN_COMPILER_H

#include <cstdio>

#include <Nitrogen/List.h>
#include <Nitrogen/Token.h>
#include <Nitrogen/Bytecode.h>

namespace Nitrogen {

	class Compiler {
	private:
		List<Token*>* tokens;
		List<unsigned char>* buffer;
		
	public:
		Compiler();
		~Compiler();
		
		void start();
		
		void setTokens(List<Token*>* tokens);
	};

}

#endif // NITROGEN_COMPILER_H