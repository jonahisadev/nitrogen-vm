#include <stdio.h>
#include "../api/nitrogen.h"

int print(Env* env) {
	printf("Hello native!\n");
	return 0;
}

int age(Env* env) {
	int x = getArgument(env, 8);
	printf("You are %d years old!\n", x);
	return 0;
}