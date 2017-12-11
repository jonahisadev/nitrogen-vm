#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api/nitrogen.h"
#include <dlfcn.h>

typedef int (*FUNC_PTR)(Env*);

void* n_openLibrary(const char* path);
int n_callFunction(void* lib, char* name, Env* env);
void n_closeLibrary(void* lib);

typedef struct NativeLib {
	char* name;
	void* lib;
	Env* env;
} NativeLib;

NativeLib* native_new(char* path, char* name);
int native_call_function(NativeLib* lib, char* func);
void native_bind(NativeLib* lib, Env* env);
void native_delete(NativeLib* lib);

typedef struct NativeList {
	NativeLib** data;
	int ptr;
	int size;
} NativeList;

NativeList* list_new(int size);
void list_add(NativeList* self, NativeLib* native);
NativeLib* list_get(NativeList* self, int ptr);
int list_size(NativeList* self);
NativeLib* list_find(NativeList* self, char* name);
void list_delete(NativeList* self);


//
//	IMPLEMENT
//

//	NativeLib

NativeLib* native_new(char* path, char* name) {
	NativeLib* self = (NativeLib*) malloc(sizeof(NativeLib));
	self->name = name;
	self->lib = n_openLibrary(path);
	return self;
}

int native_call_function(NativeLib* self, char* func) {
	return n_callFunction(self->lib, func, self->env);
}

void native_bind(NativeLib* self, Env* env) {
	self->env = env;
}

void native_delete(NativeLib* self) {
	n_closeLibrary(self->lib);
	free(self);
}

// NativeLib List

NativeList* list_new(int size) {
	NativeList* self = (NativeList*) malloc(sizeof(NativeList));
	self->data = (NativeLib**) malloc(sizeof(NativeLib*) * size);
	self->size = size;
	self->ptr = 0;
	return self;
}

void list_add(NativeList* self, NativeLib* native) {
	if (self->ptr >= self->size) {
		self->size *= 2;
		self->data = (NativeLib**) realloc(self->data, self->size);
	}

	self->data[self->ptr++] = native;
}

NativeLib* list_get(NativeList* self, int ptr) {
	return self->data[ptr];
}

int list_size(NativeList* self) {
	return self->ptr;
}

NativeLib* list_find(NativeList* self, char* name) {
	for (int i = 0; i < list_size(self); i++) {
		NativeLib* n = list_get(self, i);
		if (!strcmp(name, n->name)) {
			return n;
		}
	}
	return NULL;
}

void list_delete(NativeList* self) {
	free(self);
}

//	Other

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

#endif // SYSTEM_H