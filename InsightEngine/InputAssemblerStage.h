#pragma once
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

namespace insight{
	class InputAssemblerState{
	public:
		InputAssemblerState();
		~InputAssemblerState();

		void Clear( );
    	void SetDesired(InputAssemblerState* pState );
    	void Reset( );

    	unsigned int GetAvailableSlotCount();

    	TStateMonitor< int > IndexBuffer;
	    TStateMonitor< DXGI_FORMAT > IndexBufferFormat;
	    TStateArrayMonitor< int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBuffers;
	    TStateArrayMonitor< unsigned int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferStrides;
	    TStateArrayMonitor< unsigned int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferOffsets;
	    TStateMonitor< int > InputLayout;
	    TStateMonitor< D3D11_PRIMITIVE_TOPOLOGY > PrimitiveTopology;

	private:
		InputAssemblerState* _pDesired;
    	unsigned int _uAvailableSlotCount;
	};

	class InputAssemblerStage{
	public:
		InputAssemblerStage();
		~InputAssemblerStage();

		void ClearDesiredState( );
		void ClearCurrentState( );
		void ApplyDesiredState( ID3D11DeviceContext* pContext );

		const InputAssemblerState& Get() const;

		InputAssemblerState DesiredState;
	private:
		InputAssemblerState _currentState;
	};
}