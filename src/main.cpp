#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <Nitrogen/Util.h>

using namespace Nitrogen;

int main(int argc, char** argv) {
	char* src = strdup(Util::readFile(argv[1]));
	printf("%s\n", src);
	return 0;
}