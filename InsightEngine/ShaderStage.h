#pragma once
#include "Shader.h"
#include "ShaderStageState.h"

namespace insight {
	class ShaderStage {
	public:
		ShaderStage();
		virtual ~ShaderStage();

		void ClearDesiredStage();
		void ClearCurrentStage();
		void ApplyDesiredStage(ID3D11DeviceContext* pContext);

		virtual ShaderType GetType() = 0;

		virtual void BindShaderProgram(ID3D11DeviceContext* pContext) = 0;
		virtual void BindConstantBuffers(ID3D11DeviceContext* pContext) = 0;
		virtual void BindSamplerStates(ID3D11DeviceContext1* pContext) = 0;
		virtual void BindShaderResourceViews(ID3D11DeviceContext* pContext) = 0;
		virtual void BindUnorderedAccessViews(ID3D11DeviceContext* pContext) = 0;

	protected:
		ShaderStageState _derisedState;
		D3D_FEATURE_LEVEL _featureLevel;
		ShaderStageState _currentState;
	};
}