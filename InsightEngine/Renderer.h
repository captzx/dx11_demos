#pragma once
#include "Shader.h"
#include "PipeResourceProxy.h"
namespace insight {
	class SwapChainDesc;
	class RenderingPipeline;

	class PipeResource;
	class PipeResourceProxy;
	class RenderTargetView;
	class DepthStencilView;
	class Texture2D;
	class PipeBuffer;
	class SwapChain;
	class ViewPort;
	class VertexBuffer;
	class IndexBuffer;
	class ConstantBuffer;
	class IParameterManager;
	class Renderer {
	public:
		Renderer();
		~Renderer();

		static Renderer* Get();

		bool Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel);
		void Shutdown();

		int CreateSwapChain(const SwapChainDesc& swapChainDesc);

		std::shared_ptr<PipeResourceProxy> CreateTexture2D(Texture2dDesc* pConfig, D3D11_SUBRESOURCE_DATA* pData,
			ShaderResourceViewDesc* pSRVConfig = nullptr,
			RenderTargetViewDesc* pRTVConfig = nullptr,
			UnorderedAccessViewDesc* pUAVConfig = nullptr,
			DepthStencilViewDesc* pDSVConfig = nullptr);

		int CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc);
		int CreateDepthStencilView(int ResourceID, D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc);

		int CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID);
		int LoadShader(ShaderType type, LPCWSTR fileName, _In_ LPCSTR entryName, _In_ LPCSTR targetName);

		std::shared_ptr<PipeResourceProxy> CreateVertexBuffer(PipeBufferDesc* pConfig, D3D11_SUBRESOURCE_DATA* pData);
		std::shared_ptr<PipeResourceProxy> CreateIndexBuffer(PipeBufferDesc* pConfig, D3D11_SUBRESOURCE_DATA* pData);
		std::shared_ptr<PipeResourceProxy> CreateConstantBuffer(PipeBufferDesc* pConfig, D3D11_SUBRESOURCE_DATA* pData, bool bAutoUpdate = true);

		int CreateViewPort(D3D11_VIEWPORT viewport);

		void Present(HWND hWnd = 0, int SwapChain = -1, UINT SyncInterval = 0, UINT PresentFlags = 0);
	public:
		PipeResource* GetResourceByIndex(int rid);
		Texture2D* GetTexture2DByIndex(int rid);

		std::shared_ptr<PipeResourceProxy> GetSwapChainResource(int ID);

		VertexBuffer* GetVertexBufferByIndex(int rid);
		IndexBuffer* GetIndexBufferByIndex(int rid);
		ConstantBuffer* GetConstantBufferByIndex(int rid);

		RenderTargetView& GetRenderTargetViewByIndex(int rid);
		DepthStencilView& GetDepthStencilViewByIndex(int rid);

		ComPtr<ID3D11InputLayout> GetInputLayout(size_t);

		Shader* GetShader(size_t);
		const ViewPort& GetViewPort(int ID);

		RenderingPipeline* GetPipeline() const { return _pImmPipeline; }
		IParameterManager* GetParameterManager() const { return _pParameterManager; }
	protected:
		int	_GetUnusedResourceIndex();
		int	_StoreNewResource(PipeResource* pResource);
		PipeResource* _GetResourceByIndex(int ID);
	protected:
		static Renderer* _spRenderer;

		ComPtr<ID3D11Device> _pDevice;
		IParameterManager* _pParameterManager;
		RenderingPipeline* _pImmPipeline;

		std::vector<SwapChain*>	_vSwapChains;
		std::vector<ViewPort> _vViewPorts;

		std::vector <RenderTargetView>  _pRenderTargetViews;
		std::vector <DepthStencilView> _pDepthStencilViews;

		std::vector<PipeResource*> _pPipeResources;

		std::vector<Shader*> _pShaders;
		std::vector<ComPtr<ID3D11InputLayout>> _pInputLayouts;
	};
}