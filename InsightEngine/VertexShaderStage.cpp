#include "pch.h"
#include "VertexShaderStage.h"

#include "Renderer.h"
#include "VertexShader.h"

using namespace insight;

VertexShaderStage::VertexShaderStage()
{
}
//--------------------------------------------------------------------------------
VertexShaderStage::~VertexShaderStage()
{
}
//--------------------------------------------------------------------------------
ShaderType VertexShaderStage::GetType()
{
	return(VERTEX_SHADER);
}
//--------------------------------------------------------------------------------
void VertexShaderStage::BindShaderProgram(ID3D11DeviceContext* pContext){
	Renderer* pRenderer = Renderer::Get();
	Shader* pShader = pRenderer->GetShader(DesiredState.ShaderProgram.Get());

	ID3D11VertexShader* pVertexShader = 0;

	if (pShader) {
		pVertexShader = reinterpret_cast<VertexShader*>(pShader)->Get();
	}

	pContext->VSSetShader(pVertexShader, 0, 0);
}

void VertexShaderStage::BindConstantBuffers(ID3D11DeviceContext * pContext, int count){
	pContext->VSSetConstantBuffers(DesiredState.ConstantBuffers.GetStartSlot(),
		DesiredState.ConstantBuffers.GetRange(),
		DesiredState.ConstantBuffers.GetFirstSlotLocation());
}
