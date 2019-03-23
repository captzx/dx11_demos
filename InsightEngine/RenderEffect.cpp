#include "pch.h"
#include "RenderEffect.h"
#include "Shader.h"
#include "Renderer.h"
#include "RenderingPipeline.h"

#include "PipeBuffer.h"
#include "ParameterManager.h"
#include "ShaderReflection.h"
#include "RenderParameter.h"

using namespace insight;

RenderEffect::RenderEffect() {

}
RenderEffect::~RenderEffect() {

}

void RenderEffect::SetVertexShader(int index) {
	_aiIndices[VERTEX_SHADER] = index;
	_apShaders[VERTEX_SHADER] = Renderer::Get()->GetShader(index);

	if (_apShaders[VERTEX_SHADER] != nullptr) {
		if (_apShaders[VERTEX_SHADER]->GetType() != VERTEX_SHADER) {
			// Log::Get().Write(L"Trying to bind a non-vertex shader to the vertex shader...");
		}
	}

	_UpdateConstantBufferList();
}
void RenderEffect::SetPixelShader(int index) {
	_aiIndices[PIXEL_SHADER] = index;
	_apShaders[PIXEL_SHADER] = Renderer::Get()->GetShader(index);

	if (_apShaders[PIXEL_SHADER] != nullptr) {
		if (_apShaders[PIXEL_SHADER]->GetType() != PIXEL_SHADER) {
			// Log::Get().Write(L"Trying to bind a non-pixel shader to the pixel shader...");
		}
	}

	_UpdateConstantBufferList();
}

void RenderEffect::_UpdateConstantBufferList() {
	_vpConstBuffers.empty();

	for (int i = 0; i < 6; ++i) {
		Shader* pShader = _apShaders[i];

		if (pShader) {
			ShaderReflection* pReflection = pShader->GetReflection();

			for (size_t j = 0; j < pReflection->ConstantBuffers.size(); ++j) {
				RenderParameter* pParameter = pReflection->ConstantBuffers[i].pParamRef;

				bool bAlreadyThere = false;

				for (auto pExistingParameter : _vpConstBuffers) {
					if (pExistingParameter == pParameter) {
						bAlreadyThere = true;
						break;
					}
				}

				if (!bAlreadyThere) {
					_vpConstBuffers.push_back(pParameter);
				}
				else {
					// ...
				}

			}
		}
	}
}

void RenderEffect::ConfigurePipeline(RenderingPipeline* pPipeline, IParameterManager* pParameterManager) {
	for (auto pParameter : _vpConstBuffers) {
		ConstantBuffer* cbuffer = Renderer::Get()->GetConstantBufferByIndex(pParameterManager->GetConstantBufferParameter(pParameter));
		cbuffer->EvaluateMappings(pPipeline, pParameterManager);
	}

	pPipeline->BindShader(VERTEX_SHADER, _aiIndices[VERTEX_SHADER], pParameterManager);
	pPipeline->BindShader(PIXEL_SHADER, _aiIndices[PIXEL_SHADER], pParameterManager);
}

int RenderEffect::GetVertexShader() {
	return _aiIndices[VERTEX_SHADER];
}
int RenderEffect::GetPixelShader() {
	return _aiIndices[PIXEL_SHADER];
}