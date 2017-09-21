#ifndef NITROGEN_BYTECODE_H
#define NITROGEN_BYTECODE_H

namespace Nitrogen {

	enum ByteInst {
		_ICONST = 		0x01,
		_ILOAD = 		0x02,
	};
	
	enum ByteReg {
		_EAX = 			0x01,
	};

}

#endif // NITROGEN_BYTECODE_H