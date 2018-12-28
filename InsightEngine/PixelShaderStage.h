#pragma once
#include "ProgrammableStage.h"

namespace insight {
	class PixelShaderStage:public ProgrammableStage{
	public:
		PixelShaderStage();
		virtual ~PixelShaderStage();

	protected:
		virtual ShaderType GetType();

		virtual void BindShaderProgram(ID3D11DeviceContext*) override;
		virtual void BindConstantBuffers(ID3D11DeviceContext* pContext, int count) override;
	};
}
