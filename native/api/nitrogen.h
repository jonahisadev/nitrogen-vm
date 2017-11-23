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
	unsigned int* erx;
	unsigned int* erm;
} Env;

enum Registers {
	ESP,
	EBP,
	EAX,
	EBX,
	ECX,
	EDX,
	ERX,
	ERM,
};

static Env* createEnvironment(
	unsigned char* memory,
	unsigned int* sp,
	unsigned int* bp,
	unsigned int* eax,
	unsigned int* ebx,
	unsigned int* ecx,
	unsigned int* edx,
	unsigned int* erx,
	unsigned int* erm
);

static unsigned int getEnvRegister(Env* env, int reg);
static void setEnvRegister(Env* env, int reg, unsigned int value);
static int getArgument(Env* env, int off);

static unsigned int x_atoi(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

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
		unsigned int* edx,
		unsigned int* erx,
		unsigned int* erm
) {
	Env* env = (Env*) malloc(sizeof(Env));
	env->memory = memory;
	env->sp = sp;
	env->bp = bp;
	env->eax = eax;
	env->ebx = ebx;
	env->ecx = ecx;
	env->edx = edx;
	env->erx = erx;
	env->erm = erm;
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
		case ERX:
			return *(env->erx);
		case ERM:
			return *(env->erm);
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
		case ERX:
			*(env->erx) = value; break;
		case ERM:
			*(env->erm) = value; break;
	}
}

int getArgument(Env* env, int off) {
	int n = *(env->bp);
	int x = x_atoi(env->memory[n+off+0], env->memory[n+off+1], env->memory[n+off+2], env->memory[n+off+3]);
	return x;
}

unsigned int x_atoi(unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
	return (a << 24) | (b << 16) | (c << 8) | d;
}

#endif // NITROGEN_H