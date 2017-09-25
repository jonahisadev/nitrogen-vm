#ifndef NITROGEN_BYTECODE_H
#define NITROGEN_BYTECODE_H

namespace Nitrogen {

	enum ByteInst {
		_ICONST = 		0x01,
		_ILOAD = 		0x02,
		_ISTORE = 		0x03,
		_IMOV_R = 		0x04,
		_IMOV_N = 		0x05,
	};
	
	enum ByteReg {
		_EAX = 			0x01,
		_EBX = 			0x02,
		_ECX = 			0x03,
		_EDX = 			0x04,
	};
	
	class Bytecode {
	public:
		static const char* getRegister(int code);
	};

}

#endif // NITROGEN_BYTECODE_H