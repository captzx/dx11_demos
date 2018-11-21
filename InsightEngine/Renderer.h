#pragma once

namespace insight {
	class Shader;
	class ViewPort;

	class PipelineManager;
	class RenderTargetView;
	class DepthStencilView;
	class ShaderResourceView;
	class ShaderResourceViewConfig;
	class RenderTargetViewConfig;
	class UnorderedAccessViewConfig;
	class DepthStencilViewConfig;


	class BufferConfig;
	class Buffer;
	class VertexBuffer;
	class IndexBuffer;
	class ConstantBuffer;
	class Resource;
	class ResourceProxy;
	class Texture1D;
	class Texture2D;
	class Texture3D;
	class SwapChainConfig;
	class SwapChain;
	class Texture2DConfig;

	enum ShaderType;

	class Renderer {
	public:
		Renderer();
		virtual ~Renderer();

		static std::shared_ptr <Renderer> Get();

		bool Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel);
		void Shutdown();

		int CreateSwapChain(SwapChainConfig* pConfig);
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


		ResourceProxy* LoadTexture(std::string filename, bool sRGB);
		ResourceProxy* LoadTexture(void* pData, size_t bytes);
		ResourceProxy* LoadTexture(ID3D11Texture2D* pTex);
		int LoadShader(ShaderType type, std::wstring& filename, std::wstring& function,
			std::wstring& model, bool enablelogging = true);

		int LoadShader(ShaderType type, std::wstring& filename, std::wstring& function,
			std::wstring& model, const D3D_SHADER_MACRO* pDefines, bool enablelogging = true);

		// Device
		POINT GetDesktopResolution();
		D3D_FEATURE_LEVEL GetAvailableFearutrLevel(D3D_DRIVER_TYPE driverType);
		D3D_FEATURE_LEVEL GetCurrentFearutrLevel();
		UINT64 GetAvailableVideoMemory();

		PipelineManager* GetImmPipeline();

		// resource
		Resource* GetRsourceByIndex(int index);

		Buffer* GetGenericBufferByIndex(int index);
		ConstantBuffer* GetConstantBufferByIndex(int index);
		VertexBuffer* GetVertexBufferByIndex(int index);
		IndexBuffer* GetIndexBufferByIndex(int index);

		Texture2D* GetTexture2DByIndex(int index);
		SwapChain* GetSwapChainByIndex(int index);

		// resource view
		RenderTargetView& GetRenderTargetViewByIndex(int index);
		DepthStencilView& GetDepthStencilViewByIndex(int index);

		// pipeline state
		ID3D11InputLayout* GetInputLayoutByIndex(int index);

		std::shared_ptr<ResourceProxy> GetSwapChainResource(int index);

		ID3D11BlendState* GetBlendState(int index);
		ID3D11DepthStencilState* GetDepthStencilState(int index);
		ID3D11RasterizerState* GetRasterizerState(int index);
		const ViewPort& GetViewPort(int index) const;

		Shader* GetShader();
	protected:
		D3D_DRIVER_TYPE	_driverType;
		D3D_FEATURE_LEVEL _featureLevel;

		static std::shared_ptr <Renderer> _spRenderer;
		PipelineManager* _pImmPipeline;

		ID3D11Device* _pDevice;
		ID3D11Debug* _pDebugger;

		std::vector<SwapChain*> _vSwapChains;

		std::vector<Resource*> _vResources;

		std::vector<RenderTargetView> _vRenderTargetViews;
		std::vector<DepthStencilView>_vDepthStencilViews;
		std::vector<ShaderResourceView> _vShaderResourceViews;

		std::vector<Shader*> _vShaders;

		std::vector<ID3D11InputLayout*> _vInputLayouts;
		std::vector<ViewPort> _vViewPorts;
	};
}