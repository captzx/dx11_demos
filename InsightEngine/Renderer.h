#pragma once

namespace insight {
	class Buffer;
	class VertexBuffer;
	class IndexBuffer;

	class BufferConfig;

	class SwapChainConfig;

	class SwapChain;

	class ShaderResourceView;
	class RenderTargetView;

	class Shader;

	class InputLayout;

	class ViewPort;

	class PipelineManager;

	class Resource;
	class Renderer {
	public:
		Renderer();
		virtual ~Renderer();

		static std::shared_ptr <Renderer> Get();

		bool Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel);
		void Shutdown();

		void Present(HWND hWnd = 0, int SwapChain = -1, UINT SyncInterval = 0, UINT PresentFlags = 0);

		int CreateSwapChain(SwapChainConfig* pConfig);

		std::shared_ptr<Resource> CreateVertexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData);
		std::shared_ptr<Resource> CreateIndexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData);
		std::shared_ptr<Resource> CreateConstantBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData, bool bAutoUpdate = true);
		// ...

		int CreateShaderResourceView(int ResourceID, D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc);
		int CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc);
	
		int CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID);


		std::shared_ptr<ID3D11InputLayout> GetInputLayout(int index);
	protected:
		D3D_FEATURE_LEVEL _featureLevel;

		static std::shared_ptr <Renderer> _spRenderer;

		std::shared_ptr<ID3D11Device> _pDevice;

		std::vector<std::shared_ptr<Resource>> _vResources;

		std::vector<ShaderResourceView> _vShaderResourceViews;
		std::vector<RenderTargetView> _vRenderTargetViews;

		std::vector<std::shared_ptr<InputLayout>> _vInputLayouts;
		std::vector<ViewPort> _vViewPorts;

		std::vector<Shader*> _vShaders;

		PipelineManager* _pImmPipeline;

		std::vector<SwapChain*> _vSwapChains;
	};
}