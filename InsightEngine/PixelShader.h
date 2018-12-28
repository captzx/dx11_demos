#pragma once
#include "Shader.h"

namespace insight {
	class PixelShader : public Shader {
	public:
		PixelShader(ID3D11PixelShader* pShader);
		virtual ~PixelShader();

		virtual ShaderType GetType() override;
		ID3D11PixelShader* Get() { return _pPixelShader; }
	private:
		ID3D11PixelShader*	_pPixelShader = nullptr;
	};
}