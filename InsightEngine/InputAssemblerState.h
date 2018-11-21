#pragma once
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

namespace insight {
	class InputAssemblerState {
	public: 
		InputAssemblerState();
		virtual ~InputAssemblerState();

		void SetFeautureLevel(D3D_FEATURE_LEVEL level);
		unsigned int GetAvailableSlotCount();

		void CacheRunningState(InputAssemblerState* pState);

		void ClearState();
		void ResetTracing();

		TStateArrayMonitor< int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBuffers;
		TStateArrayMonitor< unsigned int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferStrides;
		TStateArrayMonitor< unsigned int, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT > VertexBufferOffsets;
		TStateMonitor<int> IndexBuffer;
		TStateMonitor<DXGI_FORMAT> IndexBufferFormat;
		TStateMonitor< int > InputLayout;
		TStateMonitor< D3D11_PRIMITIVE_TOPOLOGY > PrimitiveTopology;
	protected:
		D3D_FEATURE_LEVEL _featureLevel;
		unsigned int _uiAvailableSlotCount;

		InputAssemblerState* _pCacheState;
	};
}