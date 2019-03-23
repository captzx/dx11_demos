#include "pch.h"
#include "Shader.h"

#include "ShaderReflection.h"

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
	return false;
}

void Shader::Set(std::wstring fileName, std::string function, std::string model) {
	_wsFileName = fileName;
	_sFunction = function;
	_sShaderModel = model;
}

ShaderReflection* Shader::GetReflection() {
	return _pReflection;
}

void insight::Shader::SetCompiledShader(ID3DBlob * pCompiledShader){
	_pCompiledShader = pCompiledShader;
}

void insight::Shader::SetReflection(ShaderReflection * psr){
	_pReflection = psr;
}

ID3DBlob* insight::Shader::GetCompiledShader() const{
	return _pCompiledShader;
}
