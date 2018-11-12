#pragma once
#include "ShaderReflection.h"

namespace insight {

	class ShaderReflection;
	class Shader {
		Shader();
		virtual ~Shader();

		virtual ShaderType GetType() = 0;
		void SetReflection(ShaderReflection* pReflection);
		ShaderReflection* GetReflection();

		std::wstring ToString();

	public: 
		std::wstring _fileName;
		std::wstring _function;
		std::wstring _shaderMode;
		std::string _shaderText;
		ID3DBlob* _pCompilerShader;
		ShaderReflection* _pReflection;
	};
}