#ifndef NITROGEN_H
#define NITROGEN_H

#include <stdlib.h>

typedef struct _Env {
	unsigned char* memory;
	unsigned int* sp;
	unsigned int* bp;
	unsigned int* eax;
	unsigned int* ebx;
	unsigned int* ecx;
	unsigned int* edx;
} Env;

enum Registers {
	ESP,
	EBP,
	EAX,
	EBX,
	ECX,
	EDX
};

static Env* createEnvironment(
	unsigned char* memory,
	unsigned int* sp,
	unsigned int* bp,
	unsigned int* eax,
	unsigned int* ebx,
	unsigned int* ecx,
	unsigned int* edx
);

static unsigned int getEnvRegister(Env* env, int reg);
static void setEnvRegister(Env* env, int reg, unsigned int value);
static int getArgument(Env* env, int bpOffset);

//
// IMPLEMENTATIONS
//

Env* createEnvironment(
		unsigned char* memory,
		unsigned int* sp,
		unsigned int* bp,
		unsigned int* eax,
		unsigned int* ebx,
		unsigned int* ecx,
		unsigned int* edx
) {
	Env* env = (Env*) malloc(sizeof(Env));
	env->memory = memory;
	env->sp = sp;
	env->bp = bp;
	env->eax = eax;
	env->ebx = ebx;
	env->ecx = ecx;
	env->edx = edx;
	return env;
}

unsigned int getEnvRegister(Env* env, int reg) {
	switch (reg) {
		case ESP:
			return *(env->sp);
		case EBP:
			return *(env->bp);
		case EAX:
			return *(env->eax);
		case EBX:
			return *(env->ebx);
		case ECX:
			return *(env->ecx);
		case EDX:
			return *(env->edx);
		default:
			return (unsigned int)-1;
	}
}

void setEnvRegister(Env* env, int reg, unsigned int value) {
	switch (reg) {
		case EAX:
			*(env->eax) = value; break;
		case EBX:
			*(env->ebx) = value; break;
		case ECX:
			*(env->ecx) = value; break;
		case EDX:
			*(env->edx) = value; break;
	}
}

int getArgument(Env* env, int bpOffset) {
	int n = *(env->bp);
	int x = (env->memory[n+bpOffset]) << 24 | (env->memory[n+bpOffset-1]) << 16 | (env->memory[n+bpOffset-2]) << 8 | (env->memory[n+bpOffset-3]);
	return x;
}

#endif // NITROGEN_H