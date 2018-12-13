#pragma once

namespace insight {
	class SwapChainDesc;
	class RenderingPipeline;
	class Shader;
	enum ShaderType;
	class Renderer {
	public:
		Renderer();
		~Renderer();

		static Renderer* Get();

		bool Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel);
		void Shutdown();

		bool CreateSwapChain(const SwapChainDesc& swapChainDesc);
		bool CreateTexture2D();

		bool CreateRenderTargetView();
		bool CreateDepthStencilView();

		int CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID);
		int LoadShader(ShaderType type, std::wstring fileName, std::string entryName, std::string targetName);

		void Present();

	public:
		Shader* GetShader(int index);

		ID3D11RenderTargetView* GetRenderTargetView();
		ID3D11DepthStencilView* GetDepthStencilView();

		RenderingPipeline* GetPipeline()const { return _pImmPipeline; }
	protected:
		static Renderer* _spRenderer;

		ID3D11Device* _pDevice = nullptr;
		RenderingPipeline* _pImmPipeline = nullptr;


		IDXGISwapChain* _pSwapChain = nullptr;
		ID3D11Texture2D* _pBackBuffer = nullptr;
		D3D11_TEXTURE2D_DESC _BackBufferDesc;

		ID3D11RenderTargetView* _pRenderTargetView = nullptr;
		ID3D11DepthStencilView* _pDepthStencilView = nullptr;

		std::vector<Shader*> _vpShaders;
		std::vector<ID3D11InputLayout*> _vpInputLayouts;
		
	};
}