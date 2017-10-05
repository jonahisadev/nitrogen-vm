#ifndef NITROGEN_BYTECODE_H
#define NITROGEN_BYTECODE_H

namespace Nitrogen {

	enum ByteInst {
		_ICONST = 		0x01,
		_ILOAD = 		0x02,
		_ISTORE = 		0x03,
		_IMOV_R = 		0x04,
		_IMOV_N = 		0x05,
		
		_JMP = 			0x1D,
		_CALL = 		0x30,
		_RET = 			0x31,
	};
	
	enum ByteReg {
		_EAX = 			0x01,
		_EBX = 			0x02,
		_ECX = 			0x03,
		_EDX = 			0x04,
		
		_ESP = 			0x10,
		_EBP = 			0x11,
	};
	
	class Bytecode {
	public:
		static const char* getRegister(int code);
	};

}

#endif // NITROGEN_BYTECODE_H