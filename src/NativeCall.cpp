#include <Nitrogen/NativeCall.h>

void* n_openLibrary(const char* path) {
	void* lib = dlopen(path, RTLD_LAZY);
	return lib;
}

int n_callFunction(void* lib, char* name, Env* env) {
	FUNC_PTR func = (FUNC_PTR)dlsym(lib, name);
	int x = (*func)(env);
	return x;
}

void n_closeLibrary(void* lib) {
	dlclose(lib);
}