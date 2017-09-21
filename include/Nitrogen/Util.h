#ifndef NITROGEN_UTIL_H
#define NITROGEN_UTIL_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Nitrogen {

	class Util {
	public:
		static char* readFile(const char* path);
		static unsigned char* readBinaryFile(const char* path, int* fsize);
		
		static bool isNumber(char* str);
		static int convertNum(char* str, int base);
		
		static unsigned char* itoa(int x);
	};

}

#endif // NITROGEN_UTIL_H