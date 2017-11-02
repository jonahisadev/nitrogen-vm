#ifndef NITROGEN_COMPILER_H
#define NITROGEN_COMPILER_H

#include <cstdio>

#include <Nitrogen/List.h>
#include <Nitrogen/Token.h>
#include <Nitrogen/Bytecode.h>
#include <Nitrogen/Util.h>
#include <Nitrogen/Type.h>

namespace Nitrogen {

	class Compiler {
	private:
		List<Token*>* tokens;
		List<unsigned char>* buffer;
		
		List<Label*>* labels;
		List<Var*>* vars;
		List<char*>* jumps;
		List<int>* jmpAddr;
		
		List<char*>* strings;
		
		const char* entry = "start";
		int section = SEC_TEXT;
		
	public:
		Compiler();
		~Compiler();
		
		void start();
		
		void setTokens(List<Token*>* tokens);
		void setLabels(List<Label*>* labels);
		void setVars(List<Var*>* vars);
		void setJumps(List<char*>* jumps);
		void setStrings(List<char*>* strings);
		void setEntry(const char* entry);
	};

}

#endif // NITROGEN_COMPILER_H