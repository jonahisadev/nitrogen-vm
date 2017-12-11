#include <Nitrogen/NativeCall.h>

void* n_openLibrary(const char* path) {
	void* lib = dlopen(path, RTLD_LAZY);
	if (!lib) {
		printf("DYLD ERR: Could not read '%s'\n", path);
		exit(1);
	}
	return lib;
}

int n_callFunction(void* lib, char* name, Env* env) {
	FUNC_PTR func = (FUNC_PTR)dlsym(lib, name);
	if (!func) {
		printf("DYLD ERR: Could not find symbol '%s'\n", name);
		exit(1);
	}
	int x = (*func)(env);
	return x;
}

void n_closeLibrary(void* lib) {
	dlclose(lib);
}