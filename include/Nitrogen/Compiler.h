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
		List<char*>* loads;
		List<int>* jmpAddr;
		List<int>* ldAddr;
		
		List<char*>* strings;
		
		const char* entry = "start";
		int section = SEC_TEXT;
		
		int dataAddr = 0;
		
		int vsize = 0;
		
	public:
		Compiler();
		~Compiler();
		
		void start();
		void symbols(const char* path);
		
		void setTokens(List<Token*>* tokens);
		void setLabels(List<Label*>* labels);
		void setVars(List<Var*>* vars);
		void setJumps(List<char*>* jumps);
		void setLoads(List<char*>* loads);
		void setStrings(List<char*>* strings);
		void setEntry(const char* entry);
	};

}

#endif // NITROGEN_COMPILER_H