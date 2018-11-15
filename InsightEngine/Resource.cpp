#include "pch.h"
#include "Resource.h"

using namespace insight;

Resource::Resource() {
	_uInnerID = _usResourceUID;
	_usResourceUID++;
}
Resource::~Resource() {

}

unsigned short Resource::GetInnerID() {
	return _uInnerID;
}