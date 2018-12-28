#pragma once
namespace insight {
	static std::string ToAscii(const std::wstring& s);
	static std::wstring ToUnicode(const std::string& s);
}