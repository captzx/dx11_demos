#include "pch.h"
#include "Tools.h"

#include <locale>
#include <codecvt>

using namespace insight;

std::string insight::ToAscii(const std::wstring& s) {
	return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(s);
}

std::wstring insight::ToUnicode(const std::string& s) {
	return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(s);
}