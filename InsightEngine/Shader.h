#pragma once

namespace insight {
	enum ShaderType{
		VERTEX_SHADER = 0,
		HULL_SHADER = 1,
		DOMAIN_SHADER = 2,
		GEOMETRY_SHADER = 3,
		PIXEL_SHADER = 4,
		COMPUTE_SHADER = 5
	};
	enum ShaderMask{
		VERTEX_SHADER_MSK = 0x0001,
		HULL_SHADER_MSK = 0x0002,
		DOMAIN_SHADER_MSK = 0x0004,
		GEOMETRY_SHADER_MSK = 0x0008,
		PIXEL_SHADER_MSK = 0x0010,
		COMPUTE_SHADER_MSK = 0x0020
	};

	class ShaderReflection;
	class Shader {
	public:
		Shader();
		virtual ~Shader();

		virtual ShaderType GetType() = 0;
		bool IsExist(std::wstring fileName, std::string function, std::string model);
		void Set(std::wstring fileName, std::string function, std::string model);

		ShaderReflection* GetReflection();
		void SetCompiledShader(ID3DBlob* pCompiledShader);
		void SetReflection(ShaderReflection* psr);
		ID3DBlob* GetCompiledShader() const;
	protected:
		std::wstring _wsFileName;
		std::string _sFunction;
		std::string _sShaderModel;
		std::string sShaderText;
		ID3DBlob* _pCompiledShader = nullptr; 
		ShaderReflection* _pReflection = nullptr;
	};
}