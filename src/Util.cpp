#include <Nitrogen/Util.h>

namespace Nitrogen {

	char* Util::readFile(const char* path) {
		FILE* file = fopen(path, "r");
		if (!file) {
			printf("Could not open file '%s'\n", path);
			return nullptr;
		}
		
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		char* buf = new char[size];
		fread(buf, 1, size, file);
		fclose(file);
		
		return buf;
	}
	
	bool Util::isNumber(char* str) {
		int len = strlen(str);
		for (int i = 0; i < len; i++) {
			if (str[i] < '0' || str[i] > '9')
				return false;
		}
		return true;
	}
	
	int Util::convertNum(char* str, int base) {
		return strtol(str, (char**)nullptr, base);
	}

}