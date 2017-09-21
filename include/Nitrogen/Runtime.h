#ifndef NITROGEN_RUNTIME_H
#define NITROGEN_RUNTIME_H

#include <cstdio>

#include <Nitrogen/Bytecode.h>

#define RAM_SIZE 0x8000000			// 128 MB
#define STACK_START (RAM_SIZE - 0x1000 + 1)

namespace Nitrogen {

	class Runtime {
	private:
		int bin_size;
		unsigned char* prog;
		
		unsigned char* ram;
		int pc = 0;
		int sp = STACK_START;
		
	public:
		Runtime(unsigned char* prog, int bin_size);
		~Runtime();
		
		int start();
		
	private:
		void pushi(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
	};

}

#endif // NITROGEN_RUNTIME_H