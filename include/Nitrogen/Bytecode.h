#ifndef NITROGEN_BYTECODE_H
#define NITROGEN_BYTECODE_H

namespace Nitrogen {

	enum ByteInst {
		// 4 Byte Instructions
		_ICONST = 		0x01,
		_ILOAD = 		0x02,
		_ISTORE = 		0x03,
		_IMOV_R = 		0x04,
		_IMOV_N = 		0x05,
		_IADD_R = 		0x06,
		_IADD_N = 		0x07,
		_ISUB_R = 		0x08,
		_ISUB_N = 		0x09,
		_IMUL_R = 		0x0A,
		_IMUL_N = 		0x0B,
		_IDIV_R = 		0x0C,
		_IDIV_N = 		0x0D,
		_IADDR_RA = 	0x0E,
		_IADDR_RS =		0x0F,
		
		// 2 Byte Instructions
		_WCONST = 		0x11,
		_WLOAD = 		0x12,
		_WSTORE = 		0x13,
		_WMOV_R = 		0x14,
		_WMOV_N = 		0x15,
		
		// Jump Instructions
		
		_JMP = 			0x90,
		_JL = 			0x91,
		_JG = 			0x92,
		_JLE = 			0x93,
		_JGE = 			0x94,
		_JE = 			0x95,
		_JNE = 			0x96,
		
		_CMP_R = 		0xA0,
		_CMP_N = 		0xA1,
		
		// Other Instructions
		
		_CALL = 		0x10,
		_RET = 			0x20,
		_NCALL = 		0x88,
		
		_EXIT = 		0xFF,
	};
	
	enum ByteReg {
		_EAX = 			0x01,
		_EBX = 			0x02,
		_ECX = 			0x03,
		_EDX = 			0x04,
		_ERM = 			0x05,
		
		_ESP = 			0x06,
		_EBP = 			0x07,
	};
	
	class Bytecode {
	public:
		static const char* getRegister(int code);
	};

}

#endif // NITROGEN_BYTECODE_H