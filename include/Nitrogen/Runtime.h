#ifndef NITROGEN_RUNTIME_H
#define NITROGEN_RUNTIME_H

#include <cstdio>

#include <Nitrogen/Bytecode.h>
#include <Nitrogen/Util.h>

#define RAM_SIZE 0x8000000			// 128 MB
#define STACK_START (RAM_SIZE - 0x1000 + 1)

namespace Nitrogen {

	class Runtime {
	private:
		// Information
		int bin_size;
		unsigned char* prog;
		
		// CPU
		unsigned char* ram;
		int pc = 0;
		int sp = STACK_START;
		
		// Registers
		unsigned int eax;
		unsigned int ebx;
		unsigned int ecx;
		unsigned int edx;
		
	public:
		Runtime(unsigned char* prog, int bin_size);
		~Runtime();
		
		int start();
		
	private:
		void pushi(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
		void pushi(int x);
		int popi();
		
		unsigned char getNext();
		
		unsigned int* getRegister(int code);
	};

}

#endif // NITROGEN_RUNTIME_H