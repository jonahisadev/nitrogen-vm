#include "api/nitrogen.h"
#include "test.h"

int square(Env* env) {
	int x = getEnvRegister(env, EBX);
	
	int ret = n_square(x);
	
	return ret;
}