#pragma once

namespace insight {
	class Buffer;
	class VertexBuffer;
	class IndexBuffer;

	class BufferConfig;

	class SwapChainConfig;

	class SwapChain;

	class RenderTargetView;
	class DepthStencilView;
	class ShaderResourceView;

	class Shader;

	class InputLayout;

	class ViewPort;

	class PipelineManager;
	class ShaderResourceViewConfig;
	class RenderTargetViewConfig;
	class UnorderedAccessViewConfig;
	class DepthStencilViewConfig;

	class Resource;
	class ResourceProxy;
	class Renderer {
	public:
		Renderer();
		virtual ~Renderer();

		static std::shared_ptr <Renderer> Get();

		bool Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel);
		void Shutdown();

		int CreateSwapChain(SwapChainConfig* pConfig);
		std::shared_ptr<ResourceProxy> GetSwapChainResource(int swapChianIdx);
		void Present(HWND hWnd = 0, int SwapChain = -1, UINT SyncInterval = 0, UINT PresentFlags = 0);

		std::shared_ptr<ResourceProxy> CreateVertexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData);
		std::shared_ptr<ResourceProxy> CreateIndexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData);
		std::shared_ptr<ResourceProxy> CreateConstantBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData, bool bAutoUpdate = true);
		// ...

		std::shared_ptr<ResourceProxy> CreateTexture2D(Texture2DConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData,
			ShaderResourceViewConfig* pSRVConfig = nullptr,
			RenderTargetViewConfig* pRTVConfig = nullptr,
			UnorderedAccessViewConfig* pUAVConfig = nullptr,
			DepthStencilViewConfig* pDSVConfig = nullptr);

		int CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc);
		int CreateDepthStencilView(int ResourceID, D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc);
	
		int CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID);

		int CreateViewPort(D3D11_VIEWPORT viewport);

		Resource* GetResourceByIndex(int id);
		int StoreNewResource(Resource* pResource);
		int GetUnusedResourceIndex();

		int LoadShader(ShaderType type, std::wstring& filename, std::wstring& function,
			std::wstring& model, bool enablelogging = true);

		int LoadShader(ShaderType type, std::wstring& filename, std::wstring& function,
			std::wstring& model, const D3D_SHADER_MACRO* pDefines, bool enablelogging = true);

		PipelineManager* GetImmPipeline();
	protected:
		D3D_FEATURE_LEVEL _featureLevel;

		static std::shared_ptr <Renderer> _spRenderer;

		ID3D11Device* _pDevice;
		ID3D11Debug* _pDebugger;

		std::vector<Resource*> _vResources;

		std::vector<ShaderResourceView> _vShaderResourceViews;
		std::vector<RenderTargetView> _vRenderTargetViews;
		std::vector<DepthStencilView>_vDepthStencilViews;

		std::vector<std::shared_ptr<InputLayout>> _vInputLayouts;
		std::vector<ViewPort> _vViewPorts;

		std::vector<Shader*> _vShaders;

		PipelineManager* _pImmPipeline;

		std::vector<SwapChain*> _vSwapChains;
	};
}