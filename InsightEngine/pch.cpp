#include "PCH.h"


void com_safe_release(IUnknown* x) {
	if (x) {
		x->Release();
		x = NULL;
	}
}