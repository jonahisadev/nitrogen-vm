#ifndef NITROGEN_RUNTIME_H
#define NITROGEN_RUNTIME_H

#include <cstdio>
#include <cmath>

#include <Nitrogen/Bytecode.h>
#include <Nitrogen/Util.h>
#include <Nitrogen/Native.h>
#include <api/nitrogen.h>

#define RAM_SIZE 0x8000000			// 128 MB
#define STACK_START (RAM_SIZE - 0x1000 + 1)
#define GLOBAL_START 0x1000

namespace Nitrogen {

	class Runtime {
	private:
		// Information
		int bin_size;
		unsigned char* prog;
		
		// CPU
		unsigned char* ram;
		int pc = 0;
		unsigned int sp = STACK_START;
		unsigned int bp = STACK_START;
		
		// Registers
		unsigned int eax;
		unsigned int ebx;
		unsigned int ecx;
		unsigned int edx;
		unsigned int erx;
		unsigned int erm;
		unsigned int cmpflag;
		
		// Native
		Env* env;
		NativeLib* lsystem;
		
		// Variables
		int vsize = 0;
		
	public:
		Runtime(unsigned char* prog, int bin_size);
		~Runtime();
		
		int start();
		
	private:
		void pushi(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
		void pushi(int x);
		int popi();
		
		void pushw(unsigned char a, unsigned char b);
		void pushw(short x);
		short popw();
		
		void pushb(unsigned char a);
		unsigned char popb();
		
		unsigned char getNext();
		bool getCompare(int place);
		void compare(int a, int b);
		
		unsigned int* getRegister(int code);
	};

}

#endif // NITROGEN_RUNTIME_H