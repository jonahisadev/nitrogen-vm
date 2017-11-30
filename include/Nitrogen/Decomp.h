#ifndef NITROGEN_DECOMP_H
#define NITROGEN_DECOMP_H

#include <Nitrogen/Util.h>
#include <Nitrogen/Bytecode.h>
#include <Nitrogen/List.h>

namespace Nitrogen {

	struct Symbol {
		char* name;
		unsigned int addr;

		Symbol(char* name, unsigned int addr) {
			this->name = strdup(name);
			this->addr = addr;
		}

		~Symbol() {
			free(this->name);
		}
	};
	template class List<Symbol*>;

	class Decomp {
	private:
		unsigned char* prog;
		int bin_size;
		unsigned int pc = 0;
		
		List<Symbol*>* labels;
		List<Symbol*>* vars;
	public:
		Decomp(unsigned char* prog, int len);
		~Decomp();
		
		void start();
		unsigned char getNext();
		void loadSymbols();

		void printVar(unsigned int addr);
		void printLabel(unsigned int addr);
	};

}

#endif // NITROGEN_DECOMP_H