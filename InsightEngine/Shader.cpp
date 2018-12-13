#include "pch.h"
#include "Shader.h"

using namespace insight;

Shader::Shader() {

}
Shader::~Shader() {
	SAFE_RELEASE(_pCompiledShader)
}

bool Shader::IsExist(std::wstring fileName, std::string function, std::string model) {
	if (_wsFileName.compare(fileName) == 0 &&
		_sFunction.compare(function) == 0 &&
		_sShaderModel.compare(model) == 0) {
		return true;
	}
}

void Shader::Set(std::wstring fileName, std::string function, std::string model) {
	_wsFileName = fileName;
	_sFunction = function;
	_sShaderModel = model;
}

void insight::Shader::SetCompiledShader(ID3DBlob * pCompiledShader){
	_pCompiledShader = pCompiledShader;
}

ID3DBlob* insight::Shader::GetCompiledShader() const{
	return _pCompiledShader;
}
