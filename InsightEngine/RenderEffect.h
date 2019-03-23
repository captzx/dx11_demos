#pragma once

namespace insight {
	class Shader;
	class RenderingPipeline;
	class RenderParameter;
	class IParameterManager;
	class RenderEffect {
	public:
		RenderEffect();
		~RenderEffect();

		void SetVertexShader(int index);
		void SetPixelShader(int index);

		void ConfigurePipeline(RenderingPipeline* pPipeline, IParameterManager* pParameterManager);

		int GetVertexShader();
		int GetPixelShader();
	private:
		void _UpdateConstantBufferList();
	private:
		int	_aiIndices[6];
		Shader*	_apShaders[6];

		std::vector<RenderParameter*> _vpConstBuffers;
	};
}