#include <stdio.h>
#include <stdlib.h>
#include "api/nitrogen.h"

void print_num(Env* env) {
	int x = getArgument(env, 8);
	printf("%d", x);
}

void print_char(Env* env) {
	char c = getArgument(env, 8);
	printf("%c", c);
}

void kill(Env* env) {
	exit(getEnvRegister(env, EBX));
}