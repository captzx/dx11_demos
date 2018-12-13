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

	class Shader {
	public:
		Shader();
		virtual ~Shader();

		virtual ShaderType GetType() = 0;
		bool IsExist(std::wstring fileName, std::string function, std::string model);
		void Set(std::wstring fileName, std::string function, std::string model);

		void SetCompiledShader(ID3DBlob* pCompiledShader);
		ID3DBlob* GetCompiledShader() const;
	protected:
		std::wstring _wsFileName;
		std::string _sFunction;
		std::string _sShaderModel;
		std::string sShaderText;
		ID3DBlob* _pCompiledShader = nullptr;
	};
}