#include "pch.h"
#include "PixelShader.h"

using namespace insight;

PixelShader::PixelShader(ID3D11PixelShader* pShader) {
	_pPixelShader = pShader;
}
PixelShader::~PixelShader() {

}

ShaderType PixelShader::GetType() {
	return PIXEL_SHADER;
}
