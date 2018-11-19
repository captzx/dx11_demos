#pragma once
#include "ShaderStage.h"

namespace insight {
	class HullShaderStage :public ShaderStage {
	public:
		HullShaderStage();
		virtual ~HullShaderStage();

	protected:
		virtual ShaderType GetType() override;
		virtual void BindShaderProgram(ID3D11DeviceContext* pContext) override;
		virtual void BindConstantBuffers(ID3D11DeviceContext* pContext) override;
		virtual void BindSamplerStates(ID3D11DeviceContext1* pContext) override;
		virtual void BindShaderResourceViews(ID3D11DeviceContext* pContext) override;
		virtual void BindUnorderedAccessViews(ID3D11DeviceContext* pContext) override;
	};
}