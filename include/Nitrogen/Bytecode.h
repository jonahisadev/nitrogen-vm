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
		
		// 1 Byte Instructions
		_BCONST = 		0x21,
		_BLOAD = 		0x22,
		_BSTORE = 		0x23,
		_BMOV_R = 		0x24,
		_BMOV_N = 		0x25,
		_BADD_R = 		0x26,
		_BADD_N = 		0x27,
		_BSUB_R = 		0x28,
		_BSUB_N = 		0x29,
		_BMUL_R = 		0x2A,
		_BMUL_N = 		0x2B,
		_BDIV_R = 		0x2C,
		_BDIV_N = 		0x2D,
		
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
		_DS = 			0x3D,
		_LDS =			0x3E,
		
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
		_HINIT = 		0x70,
		_NCALL = 		0x88,
		
		// Heap Memory
		_MALLOC_N = 	0xB0,
		_MALLOC_R =		0xB1,
		
		_ISET_RA = 		0xC2,
		_ISET_RS = 		0xC3,
		_ISET_NA = 		0xC4,
		_ISET_NS = 		0xC5,
		_WSET_RA = 		0xC6,
		_WSET_RS = 		0xC7,
		_WSET_NA = 		0xC8,
		_WSET_NS = 		0xC9,
		_BSET_RA =		0xCA,
		_BSET_RS =		0xCB,
		_BSET_NA = 		0xCC,
		_BSET_NS = 		0xCD,
		
		_IGET_A = 		0xD0,
		_IGET_S = 		0xD1,
		_WGET_A = 		0xD2,
		_WGET_S = 		0xD3,
		_BGET_A = 		0xD4,
		_BGET_S = 		0xD5,
		
		_FREE = 		0xBF,
		
		_EXIT = 		0xFF,
	};
	
	enum ByteReg {
		_EAX = 			0x01,
		_EBX = 			0x02,
		_ECX = 			0x03,
		_EDX = 			0x04,
		_ERM = 			0x05,
		_ERX = 			0x06,
		
		_ESP = 			0x07,
		_EBP = 			0x08,
	};
	
	class Bytecode {
	public:
		static const char* getRegister(int code);
	};

}

#endif // NITROGEN_BYTECODE_H