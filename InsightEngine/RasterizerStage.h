#pragma once
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

namespace insight {
	class RasterizerState {
	public:
		RasterizerState();
		~RasterizerState();

		void Clear();
		void SetDesired(RasterizerState* pState);
		void Reset();

		TStateMonitor< int > ViewportCount;
		TStateArrayMonitor< int, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE > Viewports;

	private:
		RasterizerState* _pDesired;
	};

	class RasterizerStage {
	public:
		RasterizerStage();
		~RasterizerStage();

		void ClearDesiredState();
		void ClearCurrentState();
		void ApplyDesiredState(ID3D11DeviceContext* pContext);

		const RasterizerState& Get() const;

		RasterizerState DesiredState;

	private:
		RasterizerState _currentState;
	};

}