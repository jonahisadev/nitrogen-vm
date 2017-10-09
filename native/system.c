#include <stdlib.h>
#include "api/nitrogen.h"

void kill(Env* env) {
	exit(getEnvRegister(env, EBX));
}