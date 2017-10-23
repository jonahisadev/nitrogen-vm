#include <stdio.h>
#include "api/nitrogen.h"

void print_num(Env* env) {
	int x = getArgument(env, 8);
	printf("%d", x);
}

void print_char(Env* env) {
	char c = getArgument(env, 8);
	printf("%c", c);
}