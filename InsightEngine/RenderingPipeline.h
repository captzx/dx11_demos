#pragma once
#include "InputAssemblerStage.h"
#include "OutputMergerStage.h"
#include "RasterizerStage.h"
#include "VertexShaderStage.h"
#include "PixelShaderStage.h"

#include "PipeResourceProxy.h"

namespace insight {
	enum ShaderType;
	class PipeResource;
	class ConstantBuffer;
	class RenderEffect;
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
		void UpdateSubresource(ConstantBuffer* cBuffer, void*);
		void ApplyRenderTargets();

		void BindShader(ShaderType type, int ID, IParameterManager* pParameterManager);

		void ClearPipelineResources();
		void ApplyPipelineResources();

		void BindConstantBufferParameter(ShaderType type, RenderParameter* pParam, UINT slot, IParameterManager* pParamManager);

		void Draw(RenderEffect* effect, std::shared_ptr<PipeResourceProxy> vb, std::shared_ptr<PipeResourceProxy> ib, int inputLayout, D3D11_PRIMITIVE_TOPOLOGY primType, UINT vertexStride, UINT numIndices, IParameterManager* pParameterManager);

		D3D11_MAPPED_SUBRESOURCE MapResource(PipeResource* pPipeResource, UINT subresource, D3D11_MAP actions, UINT flags);
		void UnMapResource(PipeResource* pPipeResource, UINT subresource);
	public:
		InputAssemblerStage InputAssemblerStage;
		OutputMergerStage OutputMergerStage;
		RasterizerStage RasterizerStage;

		VertexShaderStage VertexShaderStage;
		PixelShaderStage PixelShaderStage;

		ProgrammableStage* apProgrammableStages[6];

	private:
		ComPtr<ID3D11DeviceContext>  _pDeviceContext;
	};

}