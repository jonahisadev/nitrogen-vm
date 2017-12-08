#include <stdio.h>
#include <stdlib.h>
#include "native.h"
#include "api/nitrogen.h"

static NativeList* nlist;

void print_num(Env* env) {
	int x = getArgument(env, 8);
	printf("%d", x);
}

void print_char(Env* env) {
	char c = getArgument(env, 8);
	printf("%c", c);
}

void initl() {
	nlist = list_new(1);
}

void openl(Env* env) {
	char* path = getString(env, getArgument(env, 8));
	char* name = getString(env, getArgument(env, 12));

	NativeLib* n = native_new(path, name);
	native_bind(n, env);
	list_add(nlist, n);
}

int ncall(char* pre, char* func) {
	NativeLib* n = list_find(nlist, pre);
	if (n) {
		return native_call_function(n, func);
	}
	printf("Native ncall error!\n");
	return -1;
}

void kill(Env* env) {
	exit(getEnvRegister(env, EBX));
}