#pragma once
#include "ProgrammableStage.h"

namespace insight {
	class VertexShaderStage:public ProgrammableStage {
	public:
		VertexShaderStage();
		virtual ~VertexShaderStage();

	protected:
		virtual ShaderType GetType();

		virtual void BindShaderProgram(ID3D11DeviceContext*);
		virtual void BindConstantBuffers(ID3D11DeviceContext* pContext, int count);
	};
}