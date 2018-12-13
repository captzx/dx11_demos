#pragma once

namespace insight {
	class Shader;
	class RenderEffect {
	public:
		RenderEffect();
		~RenderEffect();

		void SetVertexShader(int index);
		void SetPixelShader(int index);

		int GetVertexShader();
		int GetPixelShader();

	private:
		int	_aiIndices[6];
		Shader*	_apShaders[6];
	};
}