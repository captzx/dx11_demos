#pragma once

namespace insight {
	class BufferConfig;
	class Texture2DConfig;
	class Renderer;
	class ShaderResourceViewConfig;
	class RenderTargetViewConfig;
	class UnorderedAccessViewConfig;
	class DepthStencilViewConfig;
	class ResourceProxy {
	public:
		ResourceProxy();
		ResourceProxy(int ResourceID, BufferConfig* pConfig, Renderer* pRenderer,
			ShaderResourceViewConfig* pSRVConfig = NULL,
			RenderTargetViewConfig* pRTVConfig = NULL/*,
			UnorderedAccessViewConfig* pUAVConfig = NULL,
			DepthStencilViewConfig* pDSVConfig = NULL*/);
		ResourceProxy(int ResourceID, Texture2DConfig* pConfig, Renderer* pRenderer,
			ShaderResourceViewConfig* pSRVConfig = NULL,
			RenderTargetViewConfig* pRTVConfig = NULL/*,
			UnorderedAccessViewConfig* pUAVConfig = NULL,
			DepthStencilViewConfig* pDSVConfig = NULL*/);
		virtual ~ResourceProxy();
	};
}