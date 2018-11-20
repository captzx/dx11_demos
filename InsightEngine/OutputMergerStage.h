#pragma once
#include "OutputMergerStageState.h"

namespace insight {
	class OutputMergerStage {
	public:
		OutputMergerStage();
		virtual ~OutputMergerStage();

		void SetFeatureLevel(D3D_FEATURE_LEVEL);

		void ClearDesiredState();
		void ClearCurrentState();
		void ApplyDesiredRenderTargetStates(ID3D11DeviceContext* pContext);
		void ApplyDesiredBlendAndDepthStencilStates(ID3D11DeviceContext* pContext);
		void ApplyDesiredState(ID3D11DeviceContext* pContext);

		const OutputMergerStageState& GetCurrentState() const;
	private:
		D3D_FEATURE_LEVEL _featureLevel;

		OutputMergerStageState _desiredState;
		OutputMergerStageState _currentState;
	};
}