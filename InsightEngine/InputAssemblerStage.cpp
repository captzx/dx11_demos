#include "pch.h"
#include "InputAssemblerStage.h"
#include "InputAssemblerState.h"
#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace insight;

InputAssemblerStage::InputAssemblerStage() {
	DesiredState.CacheRunningState(&_currentState);
}

InputAssemblerStage::~InputAssemblerStage() {

}

void InputAssemblerStage::SetFeautureLevel(D3D_FEATURE_LEVEL level) {
	_featureLevel = level;
}

void InputAssemblerStage::ClearDesiredState() {
	DesiredState.ClearState();
}

void InputAssemblerStage::ClearCurrentState() {
	_currentState.ClearState();
}

void InputAssemblerStage::ApplyDesiredState(ID3D11DeviceContext* pContext) {
	std::shared_ptr<Renderer> pRenderer = Renderer::Get();

	if (DesiredState.InputLayout.IsNeedUpload()) {
		ID3D11InputLayout* pLayout = pRenderer->GetInputLayoutByIndex(DesiredState.InputLayout.GetState());
		if (pLayout) {
			pContext->IASetInputLayout(pLayout);
		}
		else {
			// log
		}
	}

	if (DesiredState.PrimitiveTopology.IsNeedUpload()) {
		pContext->IASetPrimitiveTopology(DesiredState.PrimitiveTopology.GetState());
	}

	if (DesiredState.VertexBuffers.IsNeedUpload() ||
		DesiredState.VertexBufferOffsets.IsNeedUpload() ||
		DesiredState.VertexBufferStrides.IsNeedUpload()) {
		ID3D11Buffer* Buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
		for (unsigned int i = 0; i < DesiredState.GetAvailableSlotCount(); ++i) {
			int index = DesiredState.VertexBuffers.GetState(i);

			VertexBuffer* pBuffer = pRenderer->GetVertexBufferByIndex(index);
			if(pBuffer) Buffers[i] = static_cast<ID3D11Buffer*>(pBuffer->GetResource());
			else Buffers[i] = nullptr;
		}

		UINT startSlot = min(DesiredState.VertexBuffers.GetStartSlot(),
			min(DesiredState.VertexBufferOffsets.GetStartSlot(),
				DesiredState.VertexBufferStrides.GetStartSlot()));

		UINT endSlot = min(DesiredState.VertexBuffers.GetEndSlot(),
			min(DesiredState.VertexBufferOffsets.GetEndSlot(),
				DesiredState.VertexBufferStrides.GetEndSlot()));

		pContext->IASetVertexBuffers(startSlot, endSlot - startSlot + 1, &Buffers[startSlot],
			DesiredState.VertexBufferStrides.GetSlotLocation(startSlot),
			DesiredState.VertexBufferOffsets.GetSlotLocation(startSlot)
		);

		if (DesiredState.IndexBuffer.IsNeedUpload()) {
			int index = DesiredState.IndexBuffer.GetState();

			IndexBuffer* pBuffer = pRenderer->GetIndexBufferByIndex(index);

			if (pBuffer) {
				ID3D11Buffer* pIndexBuffer = reinterpret_cast<ID3D11Buffer*>(pBuffer->GetResource());
				pContext->IASetIndexBuffer(pIndexBuffer, DesiredState.IndexBufferFormat.GetState(), 0);
			}
			else {
				pContext->IASetIndexBuffer(0, DesiredState.IndexBufferFormat.GetState(), 0);
			}
		}

		DesiredState.ResetTracing();
		_currentState = DesiredState;
	}
	
}

const InputAssemblerState& InputAssemblerStage::GetCurrentState() const {
	return _currentState;
}