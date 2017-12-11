#ifndef NITROGEN_NATIVECALL_H
#define NITROGEN_NATIVECALL_H

#include <dlfcn.h>
#include <api/nitrogen.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*FUNC_PTR)(Env*);

extern "C" {
void* n_openLibrary(const char* path);
int n_callFunction(void* lib, char* name, Env* env);
void n_closeLibrary(void* lib);
}

#endif // NITROGEN_NATIVECALL_H