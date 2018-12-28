#pragma once
#include "InputAssemblerStage.h"
#include "OutputMergerStage.h"
#include "RasterizerStage.h"
#include "VertexShaderStage.h"
#include "PixelShaderStage.h"

#include "PipeResourceProxy.h"

namespace insight {
	class RenderEffect;
	enum ShaderType;
	class RenderParameter;
	class IParameterManager;
	class RenderingPipeline {
	public:
		RenderingPipeline();
		~RenderingPipeline();

	public:
		void SetDeviceContext(ID3D11DeviceContext*  pDeviceContext);

		void ClearColorBuffers(const FLOAT ColorRGBA[4]);
		void ClearDepthStencilBuffers(float depth = 1.0f, UINT stencil = 0);
		//void UpdateSubresource(ID3D11Buffer * cb, ConstantBuffer* cBuffer);
		void ApplyRenderTargets();

		void BindShader(ShaderType type, int ID);

		void ClearPipelineResources();
		void ApplyPipelineResources();

		void BindConstantBufferParameter(ShaderType type, RenderParameter* pParam, UINT slot, IParameterManager* pParamManager);

		void Draw(RenderEffect* effect, ResourcePtr vb, ResourcePtr ib,
			int inputLayout, D3D11_PRIMITIVE_TOPOLOGY primType,
			UINT vertexStride, UINT numIndices);

		D3D11_MAPPED_SUBRESOURCE MapResource(PipeResource* pPipeResource, UINT subresource, D3D11_MAP actions, UINT flags);
		void UnMapResource(PipeResource* pPipeResource, UINT subresource);
	public:
		InputAssemblerStage InputAssemblerStage;
		OutputMergerStage OutputMergerStage;
		RasterizerStage RasterizerStage;

		VertexShaderStage VertexShaderStage;
		PixelShaderStage PixelShaderStage;

		ProgrammableStage* ProgrammableStage[6];

	private:
		ComPtr<ID3D11DeviceContext>  _pDeviceContext;
	};

}