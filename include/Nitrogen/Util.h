#ifndef NITROGEN_UTIL_H
#define NITROGEN_UTIL_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <Nitrogen/List.h>

namespace Nitrogen {

	class Util {
	public:
		// Files
		static char* readFile(const char* path);
		static unsigned char* readBinaryFile(const char* path, int* fsize);
		
		// String Manipulation
		static bool isNumber(char* str);
		static int convertNum(char* str, int base);
		static void toUpper(char* str);
		static char* strDupX(char* str, int start, int end);
		
		// Data Conversion
		static unsigned char* itoa(int x);
		static unsigned int atoi(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
		
		// Buffers
		static void writeInt(List<unsigned char>* list, int data);
		static void writeString(List<unsigned char>* list, char* str);
	};

}

#endif // NITROGEN_UTIL_H