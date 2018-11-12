#pragma once
#include "ShaderStage.h"

namespace insight {
	class HullShaderStage :public ShaderStage {
	public:
		HullShaderStage();
		virtual ~HullShaderStage();

	protected:
		virtual ShaderType GetType();

		virtual void BindShaderProgram(ID3D11DeviceContext* pContext);
		virtual void BindContantBuffers(ID3D11DeviceContext* pContext);
		virtual void BindSamplerStates(ID3D11DeviceContext* pContexxt);
		virtual void BindShaderResourceViews(ID3D11DeviceContext* pContext);
		virtual void BindUnordererAccessViews(ID3D11DeviceContext* pContext);
	};
}