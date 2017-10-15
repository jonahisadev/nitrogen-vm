#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "api/nitrogen.h"

void kill(Env* env) {
	exit(getEnvRegister(env, EBX));
}