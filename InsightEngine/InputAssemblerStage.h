#pragma once
#include "InputAssemblerState.h"

namespace insight {
	class InputAssemblerStage {
		InputAssemblerStage();
		virtual ~InputAssemblerStage();

		void ApplyDesiredState(ID3D11DeviceContext* pContext);

		const InputAssemblerState& GetCurrentState() const;
	protected:
		InputAssemblerState _currentState;
		InputAssemblerState _desiredState;
	};
}