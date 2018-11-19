#pragma once
#include "ShaderReflection.h"
#include "VertexShaderStage.h"
#include "HullShaderStage.h"
#include "DomainShaderStage.h"
#include "GeometryShaderStage.h"
#include "PixelShaderStage.h"
#include "ComputeShaderStage.h"

#include "InputAssemblerStage.h"
#include "RasterizerStage.h"
#include "StreamOutputStage.h"
#include "OutputMergerStage.h"

namespace insight {

	class RenderParmater;
	class IParmaterManager;

	class RenderEffect;

	class Geometry;
	class Resource;

	class PipelineManager {
	public:
		PipelineManager();
		~PipelineManager();

		void SetDeviceContext(ID3D11DeviceContext* pContext, D3D_FEATURE_LEVEL featureLevel);
		ID3D11DeviceContext* GetDeviceContext();

		void BindConstantBufferParameter(ShaderType tpye, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager);
		void BindSamplerStateParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager);
		void BindShaderResourceParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager);
		void BindUnordererAccessParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager);
		void BindShader(ShaderType type, int ID, IParmaterManager* pParmaterManager);

		void ClearInputResource();
		void ApplyInputResource();

		void ClearPipelineResources();
		void ApplyPipelineResources();

		void ClearBuffer(const FXMVECTOR& color, float depth = 1.0f, UINT stencil = 0);
		void ClearColorBuffer(const FXMVECTOR& color);
		void ClearDepthStencilBuffer(float depth, UINT stencil);

		void ClearRenderTargets();
		void SetRenderTargets();
		void ApplyRenderTargets();

		void ClearPipelineState();
		void ClearPipelineSTVs();

	private:
		static const int NumQueries = 3;
		ID3D11Query* _pQueries[NumQueries];
		ID3D11DeviceContext* _pContext;

	public:
		InputAssemblerStage InputAssemblerStage;
		VertexShaderStage VertexShaderStage;
		HullShaderStage HullShaderStage;
		DomainShaderStage DomainShaderStage;
		GeometryShaderStage GeometryShaderStage;
		StreamOutpueStage StreamOutpueStage;
		RasterizerStage RasterizerStage;
		PixelShaderStage PixelShaderStage;
		OutputMergerStage OutputMergerStage;

		ComputeShaderStage ComputeShaderStage;

		ShaderStage* ShaderStates[6];
	};
}