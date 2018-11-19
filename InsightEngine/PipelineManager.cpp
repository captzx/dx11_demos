#include "pch.h"
#include "PipelineManager.h"

using namespace insight;

PipelineManager::PipelineManager() {

}
PipelineManager::~PipelineManager(){

}

void PipelineManager::SetDeviceContext(ID3D11DeviceContext* pContext, D3D_FEATURE_LEVEL featureLevel){}
ID3D11DeviceContext* PipelineManager::GetDeviceContext(){}

void PipelineManager::BindConstantBufferParameter(ShaderType tpye, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager){}
void PipelineManager::BindSamplerStateParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager){}
void PipelineManager::BindShaderResourceParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager){}
void PipelineManager::BindUnordererAccessParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager){}
void PipelineManager::BindShader(ShaderType type, int ID, IParmaterManager* pParmaterManager){}

void PipelineManager::ClearInputResource(){}
void PipelineManager::ApplyInputResource(){}

void PipelineManager::ClearPipelineResources(){}
void PipelineManager::ApplyPipelineResources(){}

void PipelineManager::ClearBuffer(const FXMVECTOR& color, float depth, UINT stencil){}
void PipelineManager::ClearColorBuffer(const FXMVECTOR& color){}
void PipelineManager::ClearDepthStencilBuffer(float depth, UINT stencil){}

void PipelineManager::ClearRenderTargets(){}
void PipelineManager::SetRenderTargets(){}
void PipelineManager::ApplyRenderTargets(){}

void PipelineManager::ClearPipelineState(){}
void PipelineManager::ClearPipelineSTVs(){}
