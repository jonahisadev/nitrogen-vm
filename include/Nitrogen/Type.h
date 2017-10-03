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

}

#endif // NITROGEN_TYPE_H