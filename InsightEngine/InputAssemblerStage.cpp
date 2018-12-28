#include "pch.h"
#include "InputAssemblerStage.h"

#include "Renderer.h"

#include "PipeBuffer.h"

using namespace insight;

InputAssemblerState::InputAssemblerState():
  IndexBuffer( -1 ),
  IndexBufferFormat( DXGI_FORMAT_R32_UINT ),
  VertexBuffers( -1 ),
  VertexBufferStrides( 0 ),
  VertexBufferOffsets( 0 ),
  InputLayout( -1 ),
  PrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED ),
  _pDesired( nullptr ),
  _uAvailableSlotCount(D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT){

  	Clear();
}
InputAssemblerState::~InputAssemblerState(){

}

void InputAssemblerState::Clear( ){
	IndexBuffer.Initialize();
	IndexBufferFormat.Initialize();
	VertexBuffers.Initialize();
	VertexBufferStrides.Initialize();
	VertexBufferOffsets.Initialize();
	InputLayout.Initialize();
	PrimitiveTopology.Initialize();
}
void InputAssemblerState::SetDesired(InputAssemblerState* pState ){
	_pDesired = pState;

	IndexBuffer.SetDesired( &_pDesired->IndexBuffer );
	IndexBufferFormat.SetDesired( &_pDesired->IndexBufferFormat );
	VertexBuffers.SetDesired( &_pDesired->VertexBuffers );
	VertexBufferStrides.SetDesired( &_pDesired->VertexBufferStrides );
	VertexBufferOffsets.SetDesired( &_pDesired->VertexBufferOffsets );
	InputLayout.SetDesired( &_pDesired->InputLayout );
	PrimitiveTopology.SetDesired( &_pDesired->PrimitiveTopology );
}
void InputAssemblerState::Reset( ){

}

unsigned int InputAssemblerState::GetAvailableSlotCount(){
	return _uAvailableSlotCount;
}

//#####

InputAssemblerStage::InputAssemblerStage(){
	DesiredState.SetDesired( &_currentState);
}
InputAssemblerStage::~InputAssemblerStage(){
	
}

void InputAssemblerStage::ClearDesiredState( ){
	DesiredState.Clear();
}
void InputAssemblerStage::ClearCurrentState( ){
	_currentState.Clear();
}
void InputAssemblerStage::ApplyDesiredState( ID3D11DeviceContext* pContext ){
	Renderer *pRenderer = Renderer::Get();

	if(DesiredState.InputLayout.ShouldUpload()){
		ComPtr<ID3D11InputLayout> pLayout = pRenderer->GetInputLayout(DesiredState.InputLayout.Get());

		if(pLayout){
			pContext->IASetInputLayout(pLayout.Get());
		}
		else{
			// Tried to bind an invalid input layout id.
		}
	}

	if(DesiredState.PrimitiveTopology.ShouldUpload()){
		pContext->IASetPrimitiveTopology(DesiredState.PrimitiveTopology.Get());
	}

	if(DesiredState.VertexBuffers.ShouldUpload() 
		|| DesiredState.VertexBufferOffsets.ShouldUpload() 
		|| DesiredState.VertexBufferStrides.ShouldUpload()){
		ID3D11Buffer* Buffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];

		for(unsigned int i = 0; i< DesiredState.GetAvailableSlotCount(); ++i){
			int index = DesiredState.VertexBuffers.Get(i);

			VertexBuffer* pBuffer = pRenderer->GetVertexBufferByIndex(index);

			if(pBuffer){
				Buffers[i] = static_cast<ID3D11Buffer*>(pBuffer->GetResource());
			}
			else{
				Buffers[i] = 0;
			}
		}

		UINT startSlot = min(DesiredState.VertexBuffers.GetStartSlot(), 
			min(DesiredState.VertexBufferOffsets.GetStartSlot(), DesiredState.VertexBufferStrides.GetStartSlot()));
		UINT endSlot = max(DesiredState.VertexBuffers.GetEndSlot(), 
			max(DesiredState.VertexBufferStrides.GetEndSlot(), DesiredState.VertexBufferOffsets.GetEndSlot()));

	 	pContext->IASetVertexBuffers(startSlot, endSlot- startSlot +1, &Buffers[startSlot],
	 		DesiredState.VertexBufferStrides.GetSlotLocation(startSlot), DesiredState.VertexBufferOffsets.GetSlotLocation(startSlot));

	}

	if(DesiredState.IndexBuffer.ShouldUpload()){
		int index = DesiredState.IndexBuffer.Get();

		IndexBuffer* pBuffer= pRenderer->GetIndexBufferByIndex(index);

		if(pBuffer){
			ID3D11Buffer* pIndexBuffer = reinterpret_cast<ID3D11Buffer*>(pBuffer->GetResource());

			pContext->IASetIndexBuffer(pIndexBuffer, DesiredState.IndexBufferFormat.Get(), 0);
		}
		else{
			pContext->IASetIndexBuffer(nullptr, DesiredState.IndexBufferFormat.Get(), 0);
		}
	}

	//DesiredState.Reset();
	_currentState = DesiredState;
}

const InputAssemblerState& InputAssemblerStage::Get() const{
	return _currentState;
}