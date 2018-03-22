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
		buf[size] = '\0';
		
		return buf;
	}
	
	unsigned char* Util::readBinaryFile(const char* path, int* fsize) {
		FILE* file = fopen(path, "rb");
		if (!file) {
			printf("Could not open file '%s'\n", path);
			return nullptr;
		}
		
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		unsigned char* buf = new unsigned char[size];
		fread(buf, 1, size, file);
		fclose(file);
		
		*fsize = size;
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
	
	bool Util::isHex(char* str) {
		if (str[0] == '0' && str[1] == 'x') {
			// printf("valid with 0x\n");
			int len = strlen(str);
			for (int i = 2; i < len; i++) {
				if ((str[i] < '0' || str[i] > '9') &&
						(str[i] < 'A' || str[i] > 'F')) {
					// printf("i don't like %c\n", str[i]);
					return false;
				}
			}
			return true;
		} else {
			return false;
		}
	}
	
	int Util::convertNum(char* str, int base) {
		return strtol(str, (char**)nullptr, base);
	}
	
	void Util::toUpper(char* str) {
		int len = strlen(str);
		for (int i = 0; i < len; i++) {
			if (str[i] >= 'a' && str[i] <= 'z') {
				str[i] -= ('a' - 'A');
			}
		}
	}
	
	char* Util::strDupX(char* str, int start, int end) {
		char* buf = new char[end - start + 1];
		int x = 0;
		for (int i = start; i < end; i++) {
			buf[x++] = str[i];
		}
		buf[end-start] = '\0';
		return buf;
	}
	
	int Util::strlen(char* str) {
	    int len = 0;
	    while (str[len] != '\0')
	        len++;
	    return len;
	}
	
	bool Util::strcmp(char* a, char* b) {
	    int aLen = strlen(a);
	    int bLen = strlen(b);
	    
	    if (aLen != bLen)
	        return false;
	       
	    for (int i = 0; i < aLen; i++) {
	        if (a[i] != b[i])
	            return false;
	    }
	    
	    return true;
	}
	
	unsigned char* Util::itoa(int x) {
		unsigned char* arr = new unsigned char[4];
		
		arr[0] = (x >> 24) & 0xFF;
		arr[1] = (x >> 16) & 0xFF;
		arr[2] = (x >> 8)  & 0xFF;
		arr[3] = (x >> 0)  & 0xFF;
		
		return arr;
	}
	
	unsigned int Util::atoi(unsigned char a, unsigned char b, unsigned char c, unsigned char d)  {
		return (a << 24) | (b << 16) | (c << 8) | d;
	}
	
	unsigned char* Util::wtoa(short x) {
		unsigned char* arr = new unsigned char[2];
		
		arr[0] = (x >> 8) & 0xFF;
		arr[1] = (x >> 0) & 0xFF;
		
		return arr;
	}
	
	unsigned short Util::atow(unsigned char a, unsigned char b) {
		return (a << 8) | b;
	}
	
	void Util::writeInt(List<unsigned char>* list, int data) {
		unsigned char* arr = itoa(data);
		list->add(arr[0]);
		list->add(arr[1]);
		list->add(arr[2]);
		list->add(arr[3]);
		delete[] arr;
	}
	
	void Util::writeWord(List<unsigned char>* list, short data) {
		unsigned char* arr = wtoa(data);
		list->add(arr[0]);
		list->add(arr[1]);
		delete[] arr;
	}
	
	void Util::writeString(List<unsigned char>* list, char* str) {
		for (int i = 0; i < strlen(str); i++) {
			list->add((unsigned char)str[i]);
		}
		list->add(0);
	}

}