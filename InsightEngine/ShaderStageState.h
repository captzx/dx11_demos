#pragma once
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

namespace insight {
	class ShaderStageState {
		ShaderStageState();
		virtual ~ShaderStageState();

		void SetFeatureLevel(D3D_FEATURE_LEVEL level);

		void ClearState();

		void SetIntentState();
		void ResetUpdateFlags();

		TStateMonitor<int> ShaderProgram;
		TStateArrayMonitor<ID3D11Buffer*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> ConstantBuffers;
		TStateArrayMonitor<ID3D11SamplerState*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> SamplerStates;
		TStateArrayMonitor<ID3D11ShaderResourceView*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> SRVs;
		TStateArrayMonitor<ID3D11UnorderedAccessView*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> UAVs;
		TStateArrayMonitor<unsigned int, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> UAVInitialCounts;

	protected:
		D3D_FEATURE_LEVEL _featureLevel;
		ShaderStageState* _pIntentState;
	};
}