#ifndef NITROGEN_NATIVE_H
#define NITROGEN_NATIVE_H

#include <cstring>

#include <api/nitrogen.h>
#include <Nitrogen/NativeCall.h>
#include <Nitrogen/List.h>

namespace Nitrogen {

	class NativeLib {
	public:
		char* name;
		void* lib;
		Env* env;
        
	public:
		NativeLib(const char* path, const char* name);
		~NativeLib();
		
		int callFunction(char* func);
		void bind(Env* env);

		static NativeLib* getByName(List<NativeLib*>* libs, char* name);
	};

}

#endif // NITROGEN_NATIVE_H
