#include <Nitrogen/Native.h>

namespace Nitrogen {
	
	NativeLib::NativeLib(const char* path) {
		this->lib = n_openLibrary(path);
	}
	
	NativeLib::~NativeLib() {
		n_closeLibrary(this->lib);
	}
	
	int NativeLib::callFunction(char* name) {
		return n_callFunction(this->lib, name, this->env);
	}
	
	void NativeLib::bind(Env* env) {
		this->env = env;
	}

}