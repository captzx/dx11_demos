#pragma once
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

namespace insight {
	class OutputMergerState {
	public:
		OutputMergerState();
		~OutputMergerState();

		void ClearState();
		void SetDesiredState(OutputMergerState* pState);
		void ResetUpdateFlags();

		int GetRenderTargetCount() const;

		TStateMonitor<int> DepthStencilState;
		TStateMonitor<int> DepthTargetViews;
		TStateArrayMonitor<int, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> RenderTargetViews;
	protected:
		OutputMergerState* _pDesiredState;
	};

	class OutputMergerStage {
	public:
		OutputMergerStage();
		~OutputMergerStage();

		void ClearDesiredState();
		void ClearCurrentState();
		void ApplyDesiredRenderTargetStates(ID3D11DeviceContext* pContext);
		void ApplyDesiredBlendAndDepthStencilStates(ID3D11DeviceContext* pContext);
		void ApplyDesiredState(ID3D11DeviceContext* pContext);

		const OutputMergerState& GetCurrentState() const;
		OutputMergerState DesiredState;
	protected:
		OutputMergerState _currentState;
	};
}