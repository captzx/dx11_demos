#pragma once
#include "Tools.h"

namespace insight {
	class RenderParameter;
	struct ShaderInputBindDesc{
		ShaderInputBindDesc(D3D11_SHADER_INPUT_BIND_DESC desc){
			Name = std::wstring(ToUnicode(std::string(desc.Name)));
			Type = desc.Type;
			BindPoint = desc.BindPoint;
			BindCount = desc.BindCount;
			uFlags = desc.uFlags;
			ReturnType = desc.ReturnType;
			Dimension = desc.Dimension;
			NumSamples = desc.NumSamples;
			pParamRef = 0;
		};

		ShaderInputBindDesc(){
			Name = std::wstring(L"");
			Type = D3D_SIT_CBUFFER;
			BindPoint = 0;
			BindCount = 0;
			uFlags = 0;
			ReturnType = D3D11_RETURN_TYPE_UNORM;
			Dimension = D3D_SRV_DIMENSION_UNKNOWN;
			NumSamples = 0;
			pParamRef = 0;
		};

		std::wstring Name;
		D3D_SHADER_INPUT_TYPE Type;
		UINT BindPoint;
		UINT BindCount;
		UINT uFlags;
		D3D11_RESOURCE_RETURN_TYPE ReturnType;
		D3D_SRV_DIMENSION Dimension;
		UINT NumSamples;
		RenderParameter* pParamRef;
	};

	struct ConstantBufferLayout{
		D3D11_SHADER_BUFFER_DESC				Description;
		std::vector<D3D11_SHADER_VARIABLE_DESC>	Variables;
		std::vector<D3D11_SHADER_TYPE_DESC>		Types;
		std::vector<RenderParameter*>		Parameters;
		RenderParameter*					pParamRef;
	};

	class IParameterManager;
	class RenderingPipeline;
	enum ShaderType;
	class ShaderReflection {
	public:
		ShaderReflection();
		~ShaderReflection();

	public:
		void InitializeConstantBuffers(IParameterManager* pParameterManager);
		void UpdateParameters(RenderingPipeline* pImmPipeline, IParameterManager* pParameterManager);
		void BindParameters(ShaderType type, RenderingPipeline* pImmPipeline, IParameterManager* pParameterManager);

		void PrintShaderDetails();

		void SetName(const std::wstring& name);
		std::wstring GetName();

	public:
		std::wstring Name;
		D3D11_SHADER_DESC								ShaderDescription;
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC>		InputSignatureParameters;
		std::vector<D3D11_SIGNATURE_PARAMETER_DESC>		OutputSignatureParameters;
		std::vector<ConstantBufferLayout>				ConstantBuffers;
		std::vector<ShaderInputBindDesc>				ResourceBindings;
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