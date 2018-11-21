#include "pch.h"
#include "InputAssemblerState.h"

using namespace insight;

InputAssemblerState::InputAssemblerState():
	IndexBuffer(-1),
	IndexBufferFormat(DXGI_FORMAT_R32_UINT),
	VertexBuffers(-1),
	VertexBufferStrides(0),
	VertexBufferOffsets(0),
	InputLayout(-1),
	PrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED),
	_featureLevel(D3D_FEATURE_LEVEL_11_0),
	_uiAvailableSlotCount(0) {

	ClearState();
}
InputAssemblerState::~InputAssemblerState() {

}


void InputAssemblerState::SetFeautureLevel(D3D_FEATURE_LEVEL level) {
	_featureLevel = level;

	if (_featureLevel == D3D_FEATURE_LEVEL_11_0) {
		_uiAvailableSlotCount = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
	}
	else {
		_uiAvailableSlotCount = D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
	}
}

void InputAssemblerState::CacheRunningState(InputAssemblerState* pState) {
	_pCacheState = pState;

	IndexBuffer.CacheRunningState(&pState->IndexBuffer);
	IndexBufferFormat.CacheRunningState(&pState->IndexBufferFormat);
	VertexBuffers.CacheRunningState(&pState->VertexBuffers);
	VertexBufferStrides.CacheRunningState(&pState->VertexBufferStrides);
	VertexBufferOffsets.CacheRunningState(&pState->VertexBufferOffsets);
	InputLayout.CacheRunningState(&pState->InputLayout);
	PrimitiveTopology.CacheRunningState(&pState->PrimitiveTopology);
}

void InputAssemblerState::ClearState() {
	IndexBuffer.InitializeState();
	IndexBufferFormat.InitializeState();
	VertexBuffers.InitializeState();
	VertexBufferStrides.InitializeState();
	VertexBufferOffsets.InitializeState();
	InputLayout.InitializeState();
	PrimitiveTopology.InitializeState();
}

void InputAssemblerState::ResetTracing() {
	IndexBuffer.ResetTracing();
	IndexBufferFormat.ResetTracing();
	VertexBuffers.ResetTracing();
	VertexBufferStrides.ResetTracing();
	VertexBufferOffsets.ResetTracing();
	InputLayout.ResetTracing();
	PrimitiveTopology.ResetTracing();
}

unsigned int InputAssemblerState::GetAvailableSlotCount() {
	return D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
}
