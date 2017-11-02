#ifndef NITROGEN_TYPE_H
#define NITROGEN_TYPE_H

#include <cstdlib>

#include <Nitrogen/List.h>

namespace Nitrogen {

	struct Label {
		char* name;
		int addr;
		
		Label(char* name, int addr) {
			this->name = strdup(name);
			this->addr = addr;
		}
		
		~Label() {
			free(this->name);
		}
	};
	template class List<Label*>;
	
	struct Var {
		char* name;
		int addr;
		int data;
		int size;
		
		Var(char* name, int addr) {
			this->name = strdup(name);
			this->addr = addr;
		}
		
		~Var() {
			free(this->name);
		}
	};
	template class List<Var*>;

}

#endif // NITROGEN_TYPE_H