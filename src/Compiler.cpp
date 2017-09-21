#include <Nitrogen/Compiler.h>

namespace Nitrogen {

	Compiler::Compiler() {
		this->buffer = new List<unsigned char>(1);
	}
	
	Compiler::~Compiler() {
		delete this->buffer;
	}
	
	void Compiler::start() {
		for (int i = 0; i < tokens->getSize(); i++) {
			if (tokens->get(i)->getType() == INST) {
				// ICONST
				if (tokens->get(i)->getData() == ICONST &&
						tokens->get(i+1)->getType() == NUM) {
					buffer->add(_ICONST);
					unsigned char* data = Util::itoa(tokens->get(i+1)->getData());
					buffer->add(data[0]);
					buffer->add(data[1]);
					buffer->add(data[2]);
					buffer->add(data[3]);
				}
			}
		}
		
		FILE* out = fopen("out.nc", "wb");
		for (int i = 0; i < this->buffer->getSize(); i++) {
			unsigned char b = this->buffer->get(i);
			fwrite(&b, 1, 1, out);
		}
		fclose(out);
	}

	void Compiler::setTokens(List<Token*>* tokens) {
		this->tokens = tokens;
	}

}