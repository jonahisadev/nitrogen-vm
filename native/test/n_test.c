#include "../api/nitrogen.h"
#include "test.h"

int n_add(Env* env) {
	int x = getArgumenti(env, 8);
	int y = getArgumenti(env, 12);

	return add(x, y);
}