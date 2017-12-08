#include <Nitrogen/Native.h>

namespace Nitrogen {
	
	NativeLib::NativeLib(const char* path, const char* name) {
		this->lib = n_openLibrary(path);
		this->name = strdup(name);
	}
	
	NativeLib::~NativeLib() {
		n_closeLibrary(this->lib);
		free(this->name);
	}
	
	int NativeLib::callFunction(char* func) {
		return n_callFunction(this->lib, func, this->env);
	}
	
	void NativeLib::bind(Env* env) {
		this->env = env;
	}

	NativeLib* NativeLib::getByName(List<NativeLib*>* libs, char* name) {
		for (int i = 0; i < libs->getSize(); i++) {
			if (!strcmp(libs->get(i)->name, name)) {
				return libs->get(i);
			}
		}
		return nullptr;
	}

}