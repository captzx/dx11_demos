#pragma once
#include "ShaderStage.h"

namespace insight {
	class VertexShaderStage: public ShaderStage {
	public:
		VertexShaderStage();
		virtual ~VertexShaderStage();

	protected: 
		virtual ShaderType GetType();
		virtual void BindShaderProgram(ID3D11DeviceContext* pContext);
		virtual void BindContextBuffers(ID3D11DeviceContext* pContext);
		virtual void BindSamplerStates(ID3D11DeviceContext* pContext);
		virtual void BindShaderResourceView(ID3D11DeviceContext* pContext);
		virtual void BindUnordererAccessView(ID3D11DeviceContext* pContext);
	};
}