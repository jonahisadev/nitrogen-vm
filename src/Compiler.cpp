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
					Util::writeInt(buffer, tokens->get(i+1)->getData());
				}
				
				// ILOAD
				else if (tokens->get(i)->getData() == ILOAD &&
						tokens->get(i+1)->getType() == REG) {
					buffer->add(_ILOAD);
					buffer->add(tokens->get(i+1)->getData() + 1);
				}
				
				// ISTORE
				else if (tokens->get(i)->getData() == ISTORE &&
						tokens->get(i+1)->getType() == REG) {
					buffer->add(_ISTORE);
					buffer->add(tokens->get(i+1)->getData() + 1);
				}
				
				// IMOV
				else if (tokens->get(i)->getData() == IMOV &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_IMOV_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_IMOV_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeInt(buffer, tokens->get(i+2)->getData());
					}
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