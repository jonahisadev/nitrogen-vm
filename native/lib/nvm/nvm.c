#include "nvm.h"

int println(Env* env) {
	char* str = getString(env, getArgumenti(env, 8));
	printf("%s\n", str);
	return 0;
}

int add(Env* env) {
	int a = getArgumenti(env, 8);
	int b = getArgumenti(env, 12);

	return a + b;
}