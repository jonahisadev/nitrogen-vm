#ifndef NITROGEN_NATIVE_H
#define NITROGEN_NATIVE_H

#include <api/nitrogen.h>
#include <Nitrogen/NativeCall.h>

namespace Nitrogen {

	class NativeLib {
	private:
		void* lib;
		Env* env;
		
	public:
		NativeLib(const char* path);
		~NativeLib();
		
		int callFunction(char* name);
		void bind(Env* env);
	};

}

#endif // NITROGEN_NATIVE_H