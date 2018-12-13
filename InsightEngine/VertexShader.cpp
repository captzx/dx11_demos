#include "pch.h"
#include "VertexShader.h"

using namespace insight;

VertexShader::VertexShader(ID3D11VertexShader* pShader) {
	_pVertexShader = pShader;
}
VertexShader::~VertexShader() {

}

ShaderType VertexShader::GetType() {
	return VERTEX_SHADER;
}
