#include <stdio.h>
#include "api/nitrogen.h"

void printNum(Env* env) {
	printf("%d\n", getEnvRegister(env, EBX));
}

int square(Env* env) {
	int x = getEnvRegister(env, EBX);
	return x * x;
}