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
		PipelineManager();
		~PipelineManager();

		void SetDeviceContext(std::shared_ptr<ID3D11DeviceContext> pContext, D3D_FEATURE_LEVEL featureLevel);
		ID3D11DeviceContext* GetDeviceContext();

		void BindConstantBufferParameter(ShaderType tpye, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager);
		void BindSamplerStateParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager);
		void BindShaderResourceParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager);
		void BindUnordererAccessParmater(ShaderType type, RenderParmater* pParmater, UINT slot, IParmaterManager* pParmaterManager);
		void BindShader(ShaderType type, int ID, IParmaterManager* pParmaterManager);

		void ApplyInputResource();
		void ClearInputResource();

		void ApplyPipelineResources();
		void ClearPipelineResources();

		void ClearRenderTargets();
		void ClearRenderTargets();

		void ClearPipelineState();
		void ClearPipelineSTVs();


	private:
		std::shared_ptr<ID3D11DeviceContext> _pContext;

		VertexShaderStage _vertexShaderStage;
		HullShaderStage _hullShaderStage;
		DomainShaderStage _domainShaderStage;
		GeometryShaderStage _geometryShaderStage;
		PixelShaderStage _pixelShaderStage;
		ComputeShaderStage _computeShaderStage;

		ShaderStage ShaderStates[6];

		InputAssemblerStage _inputAssemblerStage;
		StreamOutpueStage _streamOutputStage;
		RasterizerStage _rasterizerStage;
		OutputMergerStage _outputMergerStage;
	
	
	
	};
}