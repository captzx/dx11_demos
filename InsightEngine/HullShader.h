#pragma once
#include "ShaderStage.h"

namespace insight {
	class HullShader :public ShaderStage {
	public: 
		HullShader();
		virtual ~HullShader();

	protected:
		virtual ShaderType GetType();
		
		virtual void BindShaderProgram(ID3D11DeviceContext* pContext);
		virtual void BindConstantBuffers(ID3D11DeviceContext* pContext);
		virtual void BindSamplerStates(ID3D11DeviceContext* pContext);
		virtual void BindShaderResourceView(ID3D11DeviceContext* pContext);
		virtual void BindUnordererAccessView(ID3D11DeviceContext* pContext);
	};
}