#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <Nitrogen/Util.h>
#include <Nitrogen/Parser.h>

using namespace Nitrogen;

int main(int argc, char** argv) {
	char* src = Util::readFile(argv[1]);
	
	Parser* p = new Parser(src);
	p->start();
	p->printTokens();
	delete p;
	
	return 0;
}