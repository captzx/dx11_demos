#pragma once

namespace insight {
	class Shader;
	class RenderingPipeline;
	class ConstantBuffer;
	class RenderEffect {
	public:
		RenderEffect();
		~RenderEffect();

		void SetVertexShader(int index);
		void SetPixelShader(int index);

		void ConfigurePipeline(RenderingPipeline* pPipeline);

		int GetVertexShader();
		int GetPixelShader();

	private:
		int	_aiIndices[6];
		Shader*	_apShaders[6];

		std::vector<ConstantBuffer*> _vpConstBuffers;
	};
}