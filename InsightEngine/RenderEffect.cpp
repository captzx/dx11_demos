#include "pch.h"
#include "RenderEffect.h"
#include "Shader.h"
#include "Renderer.h"

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
}
void RenderEffect::SetPixelShader(int index) {
	_aiIndices[PIXEL_SHADER] = index;
	_apShaders[PIXEL_SHADER] = Renderer::Get()->GetShader(index);

	if (_apShaders[PIXEL_SHADER] != nullptr) {
		if (_apShaders[PIXEL_SHADER]->GetType() != PIXEL_SHADER) {
			// Log::Get().Write(L"Trying to bind a non-pixel shader to the pixel shader...");
		}
	}
}

int RenderEffect::GetVertexShader() {
	return _aiIndices[VERTEX_SHADER];
}
int RenderEffect::GetPixelShader() {
	return _aiIndices[PIXEL_SHADER];
}