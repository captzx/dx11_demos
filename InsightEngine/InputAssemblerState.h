#pragma once
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

namespace insight {
	class InputAssemblerState {
	public: 
		InputAssemblerState();
		virtual ~InputAssemblerState();


		TStateArrayMonitor< int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBuffers;
		TStateArrayMonitor< unsigned int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferStrides;
		TStateArrayMonitor< unsigned int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferOffsets;
		TStateMonitor<int> IndexBuffer;
		TStateMonitor<DXGI_FORMAT> IndexBufferFormat;
		TStateMonitor< int > InputLayout;
		TStateMonitor< D3D11_PRIMITIVE_TOPOLOGY > PrimitiveTopology;
		
		unsigned int GetAvailableSlotCount() { return D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT };

	protected:
		InputAssemblerState* _state;

	};
}