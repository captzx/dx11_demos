#pragma once
#include "Tools.h"

namespace insight {
	class RenderParameter;
	struct ShaderInputBindDesc{
	public:
		ShaderInputBindDesc() {};
		ShaderInputBindDesc(D3D11_SHADER_INPUT_BIND_DESC desc){
			Name = std::wstring(ToUnicode(std::string(desc.Name)));
			Type = desc.Type;
			BindPoint = desc.BindPoint;
			BindCount = desc.BindCount;
			uFlags = desc.uFlags;
			ReturnType = desc.ReturnType;
			Dimension = desc.Dimension;
			NumSamples = desc.NumSamples;
		};

	public:
		std::wstring Name = std::wstring(L"");
		D3D_SHADER_INPUT_TYPE Type = D3D_SIT_CBUFFER;
		UINT BindPoint = 0;
		UINT BindCount = 0;
		UINT uFlags = 0;
		D3D11_RESOURCE_RETURN_TYPE ReturnType = D3D11_RETURN_TYPE_UNORM;
		D3D_SRV_DIMENSION Dimension = D3D_SRV_DIMENSION_UNKNOWN;
		UINT NumSamples = 0;

		RenderParameter* pParameterRef = nullptr;
	};

	struct ConstantBufferLayout{
		D3D11_SHADER_BUFFER_DESC Description;
		std::vector<D3D11_SHADER_VARIABLE_DESC>	Variables;
		std::vector<D3D11_SHADER_TYPE_DESC>	Types;
		std::vector<RenderParameter*> Parameters;
		RenderParameter* pParameterRef;
	};

	enum ShaderType;
	class IParameterManager;
	class RenderingPipeline;
	class ShaderReflection {
	public:
		ShaderReflection();
		~ShaderReflection();

	public:
		void InitializeConstantBuffers(IParameterManager* pParameterManager);
		void UpdateParameters(RenderingPipeline* pIPipeline, IParameterManager* pParameterManager);
		void BindParameters(ShaderType type, RenderingPipeline* pPipeline, IParameterManager* pParameterManager);

		void SetName(const std::wstring& name);
		std::wstring GetName();

	public:
		std::wstring Name;
		D3D11_SHADER_DESC ShaderDescription;
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC> InputSignatureParameters;
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC>	OutputSignatureParameters;
		std::vector<ConstantBufferLayout> ConstantBuffers;
		std::vector<ShaderInputBindDesc> ResourceBindings;
	};

	class Shader;
	class ShaderReflectionFactory {
	public:
		~ShaderReflectionFactory() {}
	private:
		ShaderReflectionFactory() {}

	public:
		static ShaderReflection* GenerateReflection(Shader& shader);
	};
}