#pragma once

namespace insight {
	class Renderer;

	class PipeBufferDesc;
	class Texture1dDesc;
	class Texture2dDesc;
	class Texture3dDesc;
	class RenderTargetViewDesc;
	class DepthStencilViewDesc;
	class ShaderResourceViewDesc;
	class UnorderedAccessViewDesc;

	class PipeResourceProxy {
	public:
		PipeResourceProxy();
		PipeResourceProxy(int ResourceID, PipeBufferDesc* pDesc, Renderer* pRenderer,
			ShaderResourceViewDesc* pSRVDesc = nullptr,
			RenderTargetViewDesc* pRTVDesc = nullptr,
			UnorderedAccessViewDesc* pUAVDesc = nullptr);
		PipeResourceProxy(int ResourceID, Texture1dDesc* pDesc, Renderer* pRenderer,
			ShaderResourceViewDesc* pSRVDesc = nullptr,
			RenderTargetViewDesc* pRTVDesc = nullptr,
			UnorderedAccessViewDesc* pUAVDesc = nullptr);

		PipeResourceProxy(int ResourceID, Texture2dDesc* pDesc, Renderer* pRenderer,
			ShaderResourceViewDesc* pSRVDesc = nullptr,
			RenderTargetViewDesc* pRTVDesc = nullptr,
			UnorderedAccessViewDesc* pUAVDesc = nullptr,
			DepthStencilViewDesc* pDSVDesc = nullptr);
		PipeResourceProxy(int ResourceID, Texture3dDesc* pDesc, Renderer* pRenderer,
			ShaderResourceViewDesc* pSRVDesc = nullptr,
			RenderTargetViewDesc* pRTVDesc = nullptr,
			UnorderedAccessViewDesc* pUAVDesc = nullptr);

		virtual ~PipeResourceProxy();
	protected:
		void _CreateViewByBindFlags(UINT BindFlags, int ResourceID, Renderer* pRenderer,
			ShaderResourceViewDesc* pSRVConfig,
			RenderTargetViewDesc* pRTVConfig,
			UnorderedAccessViewDesc* pUAVConfig,
			DepthStencilViewDesc* pDSVConfig = nullptr);
	public:
		int						_iResource = -1;
		int						_iResourceSRV = 0;
		int						_iResourceRTV = 0;
		int						_iResourceDSV = 0;
		int						_iResourceUAV = 0;

		PipeBufferDesc*		    _pBufferDesc = nullptr;
		Texture1dDesc*	        _pTexture1dDesc = nullptr;
		Texture2dDesc*	        _pTexture2dDesc = nullptr;
		Texture3dDesc*	        _pTexture3dDesc = nullptr;
		DepthStencilViewDesc*   _pDSVDesc = nullptr;
		ShaderResourceViewDesc* _pSRVDesc = nullptr;
		RenderTargetViewDesc*   _pRTVDesc = nullptr;
		UnorderedAccessViewDesc*_pUAVDesc = nullptr;
	};
}