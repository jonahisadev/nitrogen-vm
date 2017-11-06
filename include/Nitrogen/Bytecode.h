#ifndef NITROGEN_BYTECODE_H
#define NITROGEN_BYTECODE_H

namespace Nitrogen {

	enum ByteInst {
		_NOP = 			0x00,
		
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
		_WADD_R = 		0x16,
		_WADD_N = 		0x17,
		_WSUB_R = 		0x18,
		_WSUB_N = 		0x19,
		_WMUL_R = 		0x1A,
		_WMUL_N = 		0x1B,
		_WDIV_R = 		0x1C,
		_WDIV_N = 		0x1D,
		_WADDR_RA = 	0x1E,
		_WADDR_RS = 	0x1F,
		
		// Variable Instructions
		_DB = 			0x31,
		_DW = 			0x32,
		_DD = 			0x33,
		_LDB = 			0x34,
		_LDW = 			0x35,
		_LDD = 			0x36,
		_STB_VR = 		0x37,
		_STW_VR = 		0x38,
		_STD_VR = 		0x39,
		_STB_VN = 		0x3A,
		_STW_VN = 		0x3B,
		_STD_VN = 		0x3C,
		
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
		_INC = 			0x30,
		_DEC = 			0x40,
		_PUSHA = 		0x50,
		_POPA = 		0x60,
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