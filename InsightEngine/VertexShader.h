#pragma once
#include "Shader.h"

namespace insight {
	class VertexShader : public Shader {
	public:
		VertexShader(ID3D11VertexShader* pShader);
		virtual ~VertexShader();

		virtual ShaderType GetType() override;

	private:
		ID3D11VertexShader*	_pVertexShader = nullptr;
	};
}