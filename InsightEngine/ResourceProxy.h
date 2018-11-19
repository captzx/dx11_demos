#pragma once

namespace insight {
	class BufferConfig;
	class Texture2DConfig;
	class Texture1DConfig;
	class Texture3DConfig;
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

	public:
		int						_iResource;
		int						_iResourceSRV;
		int						_iResourceRTV;
		int						_iResourceDSV;
		int						_iResourceUAV;

		BufferConfig*		        _pBufferConfig;
		Texture1DConfig*	        _pTexture1dConfig;
		Texture2DConfig*	        _pTexture2dConfig;
		Texture3DConfig*	        _pTexture3dConfig;
		DepthStencilViewConfig*     _pDSVConfig;
		ShaderResourceViewConfig*   _pSRVConfig;
		RenderTargetViewConfig*     _pRTVConfig;
		UnorderedAccessViewConfig*  _pUAVConfig;
	};
}