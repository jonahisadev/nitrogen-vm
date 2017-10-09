#include <Nitrogen/Bytecode.h>

namespace Nitrogen {
	
	const char* Bytecode::getRegister(int code) {
		switch (code) {
			case _EAX:
				return "EAX";
			case _EBX:
				return "EBX";
			case _ECX:
				return "ECX";
			case _EDX:
				return "EDX";
			case _ESP:
				return "ESP";
			case _EBP:
				return "EBP";
		}
		return "???";
	}
	
}