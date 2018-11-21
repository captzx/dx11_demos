#pragma once
#include "InputAssemblerState.h"

namespace insight {
	class InputAssemblerStage {
	public:
		InputAssemblerStage();
		virtual ~InputAssemblerStage();

		void SetFeautureLevel(D3D_FEATURE_LEVEL level);

		void ClearDesiredState();
		void ClearCurrentState();
		void ApplyDesiredState(ID3D11DeviceContext* pContext);

		const InputAssemblerState& GetCurrentState() const;


		InputAssemblerState DesiredState;
	protected:
		D3D_FEATURE_LEVEL _featureLevel;

		InputAssemblerState _currentState;
	};
}