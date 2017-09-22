#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <Nitrogen/Util.h>
#include <Nitrogen/Parser.h>
#include <Nitrogen/Runtime.h>
#include <Nitrogen/Compiler.h>
#include <Nitrogen/Decomp.h>

using namespace Nitrogen;

int main(int argc, char** argv) {
	if (!strcmp(argv[1], "-c")) {
		char* src = Util::readFile(argv[2]);
		
		Parser* p = new Parser(src);
		p->start();
		p->printTokens();
		
		Compiler* c = p->createCompiler();
		c->start();
		
		delete c;
		delete p;
		
		return 0;
	}
	
	else if (!strcmp(argv[1], "-r")) {
		int size;
		unsigned char* prog = Util::readBinaryFile(argv[2], &size);
		
		Runtime* r = new Runtime(prog, size);
		int ret = r->start();
		
		return ret;
	}
	
	else if (!strcmp(argv[1], "-d")) {
		int size;
		unsigned char* prog = Util::readBinaryFile(argv[2], &size);
		
		Decomp* d = new Decomp(prog, size);
		d->start();
		delete d;
	}
	
	else {
		printf("Invalid arguments\nTODO: show help\n");
		return 1;
	}
}