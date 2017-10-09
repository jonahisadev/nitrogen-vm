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
				
				// IADD
				else if (tokens->get(i)->getData() == IADD &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_IADD_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_IADD_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeInt(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// ISUB
				else if (tokens->get(i)->getData() == ISUB &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_ISUB_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_ISUB_N);
						buffer->add(tokens->get(i+2)->getData() + 1);
						Util::writeInt(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// IMUL
				else if (tokens->get(i)->getData() == IMUL &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_IMUL_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_IMUL_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeInt(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// IDIV
				else if (tokens->get(i)->getData() == IDIV &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_IDIV_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_IDIV_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeInt(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// IADDR
				else if (tokens->get(i)->getData() == IADDR &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						int offset = tokens->get(i+3)->getData();
						if (offset < 0) {
							buffer->add(_IADDR_RS);
							tokens->get(i+3)->setData(-offset);
						} else {
							buffer->add(_IADDR_RA);
						}
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
						buffer->add(tokens->get(i+3)->getData());
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
				
				// CALL
				else if (tokens->get(i)->getData() == CALL &&
						tokens->get(i+1)->getType() == JUMP) {
					buffer->add(_CALL);
					jmpAddr->add(i);
					tokens->get(i)->setData(this->buffer->getSize());
					Util::writeInt(buffer, 0);
				}
				
				// RET
				else if (tokens->get(i)->getData() == RET) {
					buffer->add(_RET);
				}
				
				// NCALL
				else if (tokens->get(i)->getData() == NCALL) {
					buffer->add(_NCALL);
					Util::writeString(buffer, strings->get(tokens->get(++i)->getData()));
				}
				
				else {
					printf("Serious compiler error! (Line %d)\n", tokens->get(i)->getLine());
					exit(1);
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
	
	void Compiler::setStrings(List<char*>* strings) {
		this->strings = strings;
	}

}