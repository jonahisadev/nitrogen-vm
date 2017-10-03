#include <Nitrogen/Compiler.h>

namespace Nitrogen {

	Compiler::Compiler() {
		this->buffer = new List<unsigned char>(1);
		this->jmpAddr = new List<int>(1);
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
				
				// JMP
				else if (tokens->get(i)->getData() == JMP &&
						tokens->get(i+1)->getType() == JUMP) {
					buffer->add(_JMP);
					jmpAddr->add(i);									// Set index of list for token
					tokens->get(i)->setData(this->buffer->getSize());	// Set data to address of jump addr
					Util::writeInt(buffer, 0);							// Write placeholder
				}
			}
			
			// Labels
			else if (tokens->get(i)->getType() == LABEL) {
				Label* lbl = labels->get(tokens->get(i)->getData());
				if (lbl->addr == 0) {
					lbl->addr = this->buffer->getSize();
				}
			}
		}
		
		for (int i = 0; i < jmpAddr->getSize(); i++) {
			Token* jump = tokens->get(jmpAddr->get(i));
			for (int j = 0; j < labels->getSize(); j++) {
				if (!strcmp(labels->get(j)->name, jumps->get(i))) {
					// printf("Found match for '%s'!\n", jumps->get(i));
					
					int index = jump->getData();
					unsigned char* data = Util::itoa(labels->get(j)->addr);
					for (int k = 0; k < 4; k++)
						this->buffer->set(index + k, data[k]);
					delete[] data;
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
	
	void Compiler::setLabels(List<Label*>* labels) {
		this->labels = labels;
	}
	
	void Compiler::setJumps(List<char*>* jumps) {
		this->jumps = jumps;
	}

}