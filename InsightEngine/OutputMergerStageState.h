#pragma once
#include "TStateArrayMonitor.h"
#include "TStateMonitor.h"

namespace insight {
	class OutputMergerStageState {
	public:
		OutputMergerStageState();
		virtual ~OutputMergerStageState();

		void SetFeatureLevel(D3D_FEATURE_LEVEL featureLevel);

		void ClearState();
		void CacheRunningState(OutputMergerStageState* pState);
		void ResetTracing();

		int GetRenderTargetCount() const;

		TStateArrayMonitor<int, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> RenderTargetViews;
		TStateMonitor<int> DepthStencilViews;

	protected:
		D3D_FEATURE_LEVEL _featureLevel;

		OutputMergerStageState* _pCacheState;
	};
}