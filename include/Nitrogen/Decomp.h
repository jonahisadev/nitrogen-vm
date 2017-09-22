#ifndef NITROGEN_DECOMP_H
#define NITROGEN_DECOMP_H

#include <Nitrogen/Util.h>
#include <Nitrogen/Bytecode.h>

namespace Nitrogen {

	class Decomp {
	private:
		unsigned char* prog;
		int bin_size;
		int pc = 0;
		
	public:
		Decomp(unsigned char* prog, int len);
		~Decomp();
		
		void start();
		unsigned char getNext();
	};

}

#endif // NITROGEN_DECOMP_H