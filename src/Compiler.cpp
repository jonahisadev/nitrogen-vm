#include <Nitrogen/Compiler.h>

namespace Nitrogen {

	Compiler::Compiler() {
		this->buffer = new List<unsigned char>(1);
		this->jmpAddr = new List<int>(1);
		this->ldAddr = new List<int>(1);
	}
	
	Compiler::~Compiler() {
		delete this->buffer;
	}
	
	void Compiler::start() {
		// Header
		buffer->add('N');
		buffer->add('7');
		// Data Load Call
		buffer->add(_NOP);
		Util::writeInt(buffer, 0);
		// Entry Jump
		buffer->add(_JMP);
		Util::writeInt(buffer, 0);
		
		// Instructions
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
						buffer->add(tokens->get(i+1)->getData() + 1);
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
						Util::writeInt(buffer, tokens->get(i+3)->getData());
					}
				}
				
				// WCONST
				else if (tokens->get(i)->getData() == WCONST &&
						tokens->get(i+1)->getType() == NUM) {
					buffer->add(_WCONST);
					Util::writeWord(buffer, tokens->get(i+1)->getData());
				}
				
				// WLOAD
				else if (tokens->get(i)->getData() == WLOAD &&
						tokens->get(i+1)->getType() == REG) {
					buffer->add(_WLOAD);
					buffer->add(tokens->get(i+1)->getData() + 1);
				}
				
				// WSTORE
				else if (tokens->get(i)->getData() == WSTORE &&
						tokens->get(i+1)->getType() == REG) {
					buffer->add(_WSTORE);
					buffer->add(tokens->get(i+1)->getData() + 1);
				}
				
				// WMOV
				else if (tokens->get(i)->getData() == WMOV &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_WMOV_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_WMOV_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeWord(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// WADD
				else if (tokens->get(i)->getData() == WADD &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_WADD_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_WADD_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeWord(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// WSUB
				else if (tokens->get(i)->getData() == WSUB &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_WSUB_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_WSUB_N);
						buffer->add(tokens->get(i+2)->getData() + 1);
						Util::writeWord(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// WMUL
				else if (tokens->get(i)->getData() == WMUL &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_WMUL_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_WMUL_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeWord(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// WDIV
				else if (tokens->get(i)->getData() == WDIV &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_WDIV_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_WDIV_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeWord(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// WADDR
				else if (tokens->get(i)->getData() == WADDR &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						int offset = tokens->get(i+3)->getData();
						if (offset < 0) {
							buffer->add(_WADDR_RS);
							tokens->get(i+3)->setData(-offset);
						} else {
							buffer->add(_WADDR_RA);
						}
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
						Util::writeInt(buffer, tokens->get(i+3)->getData());
					}
				}
				
				// BCONST
				else if (tokens->get(i)->getData() == BCONST &&
						tokens->get(i+1)->getType() == NUM) {
					buffer->add(_BCONST);
					buffer->add(tokens->get(i+1)->getData());
				}
				
				// BLOAD
				else if (tokens->get(i)->getData() == BLOAD &&
						tokens->get(i+1)->getType() == REG) {
					buffer->add(_BLOAD);
					buffer->add(tokens->get(i+1)->getData() + 1);
				}
				
				// BSTORE
				else if (tokens->get(i)->getData() == BSTORE &&
						tokens->get(i+1)->getType() == REG) {
					buffer->add(_BSTORE);
					buffer->add(tokens->get(i+1)->getData() + 1);
				}
				
				// BMOV
				else if (tokens->get(i)->getData() == BMOV &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_BMOV_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_BMOV_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData());
					}
				}
				
				// BADD
				else if (tokens->get(i)->getData() == BADD &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_BADD_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_BADD_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData());
					}
				}
				
				// BSUB
				else if (tokens->get(i)->getData() == BSUB &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_BSUB_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_BSUB_N);
						buffer->add(tokens->get(i+2)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData());
					}
				}
				
				// BMUL
				else if (tokens->get(i)->getData() == BMUL &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_BMUL_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_BMUL_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData());
					}
				}
				
				// BDIV
				else if (tokens->get(i)->getData() == BDIV &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_BDIV_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_BDIV_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData());
					}
				}
				
				// BADDR
				else if (tokens->get(i)->getData() == BADDR &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						int offset = tokens->get(i+3)->getData();
						if (offset < 0) {
							buffer->add(_BADDR_RS);
							tokens->get(i+3)->setData(-offset);
						} else {
							buffer->add(_BADDR_RA);
						}
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
						Util::writeInt(buffer, tokens->get(i+3)->getData());
					}
				}
				
				// DB
				else if (tokens->get(i)->getData() == DB &&
						tokens->get(i+1)->getType() == NUM) {
					buffer->add(_DB);
					buffer->add(tokens->get(i+1)->getData());
				}
				
				// DW
				else if (tokens->get(i)->getData() == DW &&
						tokens->get(i+1)->getType() == NUM) {
					buffer->add(_DW);
					Util::writeWord(buffer, tokens->get(i+1)->getData());
				}
				
				// DD
				else if (tokens->get(i)->getData() == DD &&
						tokens->get(i+1)->getType() == NUM) {
					buffer->add(_DD);
					Util::writeInt(buffer, tokens->get(i+1)->getData());
				}
				
				// LDB
				else if (tokens->get(i)->getData() == LDB &&
						tokens->get(i+1)->getType() == REG &&
						tokens->get(i+2)->getType() == LOAD) {
					buffer->add(_LDB);
					buffer->add(tokens->get(i+1)->getData() + 1);
					ldAddr->add(i);
					tokens->get(i)->setData(this->buffer->getSize());
					Util::writeInt(buffer, 0);
				}
				
				// LDW
				else if (tokens->get(i)->getData() == LDW &&
						tokens->get(i+1)->getType() == REG &&
						tokens->get(i+2)->getType() == LOAD) {
					buffer->add(_LDW);
					buffer->add(tokens->get(i+1)->getData() + 1);
					ldAddr->add(i);
					tokens->get(i)->setData(this->buffer->getSize());
					Util::writeInt(buffer, 0);
				}
				
				// LDD
				else if (tokens->get(i)->getData() == LDD &&
						tokens->get(i+1)->getType() == REG &&
						tokens->get(i+2)->getType() == LOAD) {
					buffer->add(_LDD);
					buffer->add(tokens->get(i+1)->getData() + 1);
					ldAddr->add(i);
					tokens->get(i)->setData(this->buffer->getSize());
					Util::writeInt(buffer, 0);
				}
				
				// STB
				else if (tokens->get(i)->getData() == STB &&
						tokens->get(i+1)->getType() == LOAD) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_STB_VR);
						ldAddr->add(i);
						tokens->get(i)->setData(this->buffer->getSize());
						Util::writeInt(buffer, 0);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_STB_VN);
						ldAddr->add(i);
						tokens->get(i)->setData(this->buffer->getSize());
						Util::writeInt(buffer, 0);
						buffer->add(tokens->get(i+2)->getData());
					}
				}
				
				// STW
				else if (tokens->get(i)->getData() == STW &&
						tokens->get(i+1)->getType() == LOAD) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_STW_VR);
						ldAddr->add(i);
						tokens->get(i)->setData(this->buffer->getSize());
						Util::writeInt(buffer, 0);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_STW_VN);
						ldAddr->add(i);
						tokens->get(i)->setData(this->buffer->getSize());
						Util::writeInt(buffer, 0);
						Util::writeWord(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// STD
				else if (tokens->get(i)->getData() == STD &&
						tokens->get(i+1)->getType() == LOAD) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_STD_VR);
						ldAddr->add(i);
						tokens->get(i)->setData(this->buffer->getSize());
						Util::writeInt(buffer, 0);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_STD_VN);
						ldAddr->add(i);
						tokens->get(i)->setData(this->buffer->getSize());
						Util::writeInt(buffer, 0);
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
				
				// INC
				else if (tokens->get(i)->getData() == INC &&
						tokens->get(i+1)->getType() == REG) {
					buffer->add(_INC);
					buffer->add(tokens->get(i+1)->getData() + 1);
				}
				
				// DEC
				else if (tokens->get(i)->getData() == DEC &&
						tokens->get(i+1)->getType() == REG) {
					buffer->add(_DEC);
					buffer->add(tokens->get(i+1)->getData() + 1);
				}
				
				// PUSHA
				else if (tokens->get(i)->getData() == PUSHA) {
					buffer->add(_PUSHA);
				}
				
				// POPA
				else if (tokens->get(i)->getData() == POPA) {
					buffer->add(_POPA);
				}
				
				// NCALL
				else if (tokens->get(i)->getData() == NCALL) {
					buffer->add(_NCALL);
					Util::writeString(buffer, strings->get(tokens->get(++i)->getData()));
				}
				
				// CMP
				else if (tokens->get(i)->getData() == CMP &&
						tokens->get(i+1)->getType() == REG) {
					if (tokens->get(i+2)->getType() == REG) {
						buffer->add(_CMP_R);
						buffer->add(tokens->get(i+1)->getData() + 1);
						buffer->add(tokens->get(i+2)->getData() + 1);
					} else if (tokens->get(i+2)->getType() == NUM) {
						buffer->add(_CMP_N);
						buffer->add(tokens->get(i+1)->getData() + 1);
						Util::writeInt(buffer, tokens->get(i+2)->getData());
					}
				}
				
				// BRANCHES
				else if (tokens->get(i)->getData() >= JL &&
						tokens->get(i)->getData() <= JNE) {
					switch (tokens->get(i)->getData()) {
						case JL:
							buffer->add(_JL); break;
						case JG:
							buffer->add(_JG); break;
						case JLE:
							buffer->add(_JLE); break;
						case JGE:
							buffer->add(_JGE); break;
						case JE:
							buffer->add(_JE); break;
						case JNE:
							buffer->add(_JNE); break;
					}
					
					jmpAddr->add(i);									// Set index of list for token
					tokens->get(i)->setData(this->buffer->getSize());	// Set data to address of jump addr
					Util::writeInt(buffer, 0);							// Write placeholder
				}
				
				// EXIT
				else if (tokens->get(i)->getData() == EXIT) {
					buffer->add(_EXIT);
				}
				
				else {
					printf("ERR: (%d) Unkown AST token\n", tokens->get(i)->getLine());
					exit(1);
				}
			}
			
			// Preprocessors
			else if (tokens->get(i)->getType() == PREPROC) {
				switch (tokens->get(i)->getData()) {
					case SEC_TEXT: {
						if (this->section == SEC_DATA)
							buffer->add(_RET);
						this->section = SEC_TEXT;
						break;
					}
					case SEC_DATA: {
						this->dataAddr = this->buffer->getSize();
						this->section = SEC_DATA;
						break;
					}
					default: {
						printf("ERR: (%d) Bad preprocessor token\n", tokens->get(i)->getLine());
						exit(1);
					}
				}
			}
			
			// Labels
			else if (tokens->get(i)->getType() == LABEL) {
				Label* lbl = labels->get(tokens->get(i)->getData());
				if (lbl->addr == 0) {
					lbl->addr = this->buffer->getSize();
				}
			}
			
			// Variables
			else if (tokens->get(i)->getType() == VAR) {
				if (tokens->get(i+1)->getType() == INST &&
				tokens->get(i+1)->getData() >= DB &&
				tokens->get(i+1)->getData() <= DD &&
				tokens->get(i+2)->getType() == NUM) {
					Var* var = vars->get(tokens->get(i)->getData());
					
					switch (tokens->get(i+1)->getData()) {
						case DB:
							var->size = 1; break;
						case DW:
							var->size = 2; break;
						case DD:
							var->size = 4; break;
					}
					
					if (var->addr == 0) {
						var->addr = vsize;
					}
					vsize += var->size;
					
					var->data = tokens->get(i+2)->getData();
					
					// printf("Variable: %s (addr 0x%08X, size %d, data %d)\n", var->name, var->addr, var->size, var->data);
				} else {
					printf("ERR: (%d) Global variable declared improperly\n", tokens->get(i)->getLine());
					exit(1);
				}
			}
		}
		
		if (this->section == SEC_DATA)
			buffer->add(_RET);
		
		// Set Addresses of Jumps and Calls
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
		
		// Set Addresses of Variable Loads
		for (int i = 0; i < ldAddr->getSize(); i++) {
			Token* load = tokens->get(ldAddr->get(i));
			for (int j = 0; j < vars->getSize(); j++) {
				if (!strcmp(vars->get(j)->name, loads->get(i))) {
					// printf("Found match for '%s'!\n", loads->get(i));
					
					int index = load->getData();
					unsigned char* data = Util::itoa(vars->get(j)->addr);
					for (int k = 0; k < 4; k++)
						this->buffer->set(index + k, data[k]);
					delete[] data;
				}
			}
		}
		
		// Set Header Entry Jump
		for (int i = 0; i < labels->getSize(); i++) {
			if (!strcmp(labels->get(i)->name, this->entry)) {
				unsigned char* data = Util::itoa(labels->get(i)->addr);
				for (int j = 0; j < 4; j++)
					this->buffer->set(8 + j, data[j]);
				delete[] data;
				break;
			}
		}
		
		// Set Header Data Load
		if (this->dataAddr != 0) {
			unsigned char* data = Util::itoa(this->dataAddr);
			this->buffer->set(2, _CALL);
			for (int j = 0; j < 4; j++)
				this->buffer->set(3 + j, data[j]);
			delete[] data;
		}
		
		// Verify Header
		if (buffer->get(0) != 'N' ||
			buffer->get(1) != '7') {
			printf("ERR: N7 Corrupt\n");
			exit(1);
		}
		if (buffer->get(7) != _JMP ||
			Util::atoi(buffer->get(8), buffer->get(9), buffer->get(10), buffer->get(11)) == 0) {
			printf("ERR: Entry '%s' not found!\n", this->entry);
			exit(1);
		}
		
		// Write Binary
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
	
	void Compiler::setVars(List<Var*>* vars) {
		this->vars = vars;
	}
	
	void Compiler::setJumps(List<char*>* jumps) {
		this->jumps = jumps;
	}
	
	void Compiler::setLoads(List<char*>* loads) {
		this->loads = loads;
	}
	
	void Compiler::setStrings(List<char*>* strings) {
		this->strings = strings;
	}
	
	void Compiler::setEntry(const char* entry) {
		this->entry = entry;
	}

}