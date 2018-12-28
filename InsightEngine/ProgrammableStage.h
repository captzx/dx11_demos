#pragma once
#include "TStateMonitor.h"
#include "TStateArrayMonitor.h"

namespace insight {
	class ProgrammableStageState {
	public:
		ProgrammableStageState();
		~ProgrammableStageState();

		void Clear();

		void SetDesired(ProgrammableStageState* pState);
		void Reset();

		TStateMonitor< int > ShaderProgram; 
		TStateArrayMonitor< ID3D11Buffer*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT >  ConstantBuffers;
	protected:
		ProgrammableStageState*	_pDesiredState;
	};

	enum ShaderType;
	class ProgrammableStage{
	public:
		ProgrammableStage();
		virtual ~ProgrammableStage();

		void ClearDesiredState();
		void ClearCurrentState();
		void ApplyDesiredState(ID3D11DeviceContext* pContext);

		virtual ShaderType GetType() = 0;

		virtual void BindShaderProgram(ID3D11DeviceContext*) = 0;
		virtual void BindConstantBuffers(ID3D11DeviceContext* pContext, int count) = 0;

		ProgrammableStageState		DesiredState;

	protected:
		ProgrammableStageState		_currentState;
	};
}