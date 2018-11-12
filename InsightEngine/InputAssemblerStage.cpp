#include "pch.h"
#include "InputAssemblerStage.h"
#include "InputAssemblerState.h"
#include "Renderer.h"

using namespace insight;

InputAssemblerStage::InputAssemblerStage() {

}

InputAssemblerStage::~InputAssemblerStage() {

}

void InputAssemblerStage::ApplyDesiredState(ID3D11DeviceContext* pContext) {
	std::shared_ptr<Renderer> pRenderer = Renderer::Get();

	if (_desiredState.InputLayout.isNeedUpload()) {
		std::shared_ptr<ID3D11InputLayout> pLayout = pRenderer->GetInputLayout(_desiredState.InputLayout.GetState());
		if (pLayout) {
			pContext->IASetInputLayout(pLayout.get());
		}
		else {
			// log
		}
	}

	if (_desiredState.PrimitiveTopology.isNeedUpload()) {
		pContext->IASetPrimitiveTopology(_desiredState.PrimitiveTopology.GetState());
	}

	if (_desiredState.VertexBuffers.IsNeedUpdate() || 
		_desiredState.VertexBufferOffsets.IsNeedUpdate() || 
		_desiredState.VertexBufferStrides.IsNeedUpdate()) {
		ID3D11Buffer* Buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
		for (unsigned int i = 0; i < _desiredState.GetAvailableSlotCount(); ++i) {
			int index = _desiredState.VertexBuffers.GetState();

			VertexBuffer* pBuffer = pRenderer->GetVertexBufferByIndex(index);
			if(pBuffer) Buffers[i] = static_cast<ID3D11Buffer*>(pBuffer->GetResource());
			else Buffers[i] = nullptr;

		}

		UINT startSlot = min(_desiredState.VertexBuffers.GetStartSlot(),
			min(_desiredState.VertexBufferOffsets.GetStartSlot(),
				_desiredState.VertexBufferStrides.GetStartSlot()));

		UINT endSlot = min(_desiredState.VertexBuffers.GetEndSlot(),
			min(_desiredState.VertexBufferOffsets.GetEndSlot(),
				_desiredState.VertexBufferStrides.GetEndSlot()));

		pContext->IASetVertexBuffers(startSlot, endSlot - startSlot + 1, &Buffers[startSlot],
			_desiredState.VertexBufferStrides.GetSlotLocation(startSlot),
			_desiredState.VertexBufferOffsets.GetSlotLocation(startSlot)
		);

		if (_desiredState.IndexBuffer.isNeedUpload()) {
			int index = _desiredState.IndexBuffer.GetState();

			IndexBuffer* pBuffer = pRenderer->GetIndexBufferByIndex(index);

			if (pBuffer) {
				ID3D11Buffer* pIndexBuffer = reinterpret_cast<ID3D11Buffer*>(pBuffer->GetResource());
				pContext->IASetIndexBuffer(pIndexBuffer, _desiredState.IndexBufferFormat.GetState(), 0);
			}
			else {
				pContext->IASetIndexBuffer(0, _desiredState.IndexBufferFormat.GetState(), 0);
			}
		}

		_desiredState.ResetUpdateFlags();
		_currentState = _desiredState;
	}
	
}

const InputAssemblerState& InputAssemblerStage::GetCurrentState() const {

}