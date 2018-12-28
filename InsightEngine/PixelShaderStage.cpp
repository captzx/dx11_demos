#include "pch.h"
#include "PixelShaderStage.h"
#include "Renderer.h"
#include "PixelShader.h"

using namespace insight;

PixelShaderStage::PixelShaderStage() {

}
PixelShaderStage::~PixelShaderStage() {

}

ShaderType PixelShaderStage::GetType() {
	return PIXEL_SHADER;
}

void PixelShaderStage::BindShaderProgram(ID3D11DeviceContext* pContext) {
	Renderer* pRenderer = Renderer::Get();
	Shader* pShader = pRenderer->GetShader(DesiredState.ShaderProgram.Get());

	ID3D11PixelShader* pPixelShader = 0;

	if (pShader) {
		pPixelShader = reinterpret_cast<PixelShader*>(pShader)->Get();
	}

	pContext->PSSetShader(pPixelShader, 0, 0);
}