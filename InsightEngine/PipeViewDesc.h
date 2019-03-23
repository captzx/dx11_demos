#pragma once

namespace insight {
	class RenderTargetViewDesc {
	public:
		RenderTargetViewDesc() { SetDefaults(); }
		~RenderTargetViewDesc() {}

		void SetDefaults();

		void SetFormat(DXGI_FORMAT Format) { _renderTargetViewDesc.Format = Format; }
		void SetViewDimension(D3D11_RTV_DIMENSION ViewDimension) { _renderTargetViewDesc.ViewDimension; }

		void SetBuffer(D3D11_BUFFER_RTV Buffer) { _renderTargetViewDesc.Buffer = Buffer; }
		void SetTexture1D(D3D11_TEX1D_RTV Texture1D) { _renderTargetViewDesc.Texture1D = Texture1D; }
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_RTV Texture1DArray) { _renderTargetViewDesc.Texture1DArray = Texture1DArray; }
		void SetTexture2D(D3D11_TEX2D_RTV Texture2D) { _renderTargetViewDesc.Texture2D = Texture2D; }
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_RTV Texture2DArray) { _renderTargetViewDesc.Texture2DArray = Texture2DArray; }
		void SetTexture2DMS(D3D11_TEX2DMS_RTV Texture2DMS) { _renderTargetViewDesc.Texture2DMS = Texture2DMS; }
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_RTV Texture2DMSArray) { _renderTargetViewDesc.Texture2DMSArray = Texture2DMSArray; }
		void SetTexture3D(D3D11_TEX3D_RTV Texture3D) { _renderTargetViewDesc.Texture3D = Texture3D; }

		D3D11_RENDER_TARGET_VIEW_DESC Get() { return _renderTargetViewDesc; }
	protected:
		D3D11_RENDER_TARGET_VIEW_DESC _renderTargetViewDesc;
	};

	class DepthStencilViewDesc{
	public:
		DepthStencilViewDesc() { SetDefaults(); }
		~DepthStencilViewDesc() {}

		void SetDefaults();

		void SetFormat(DXGI_FORMAT Format) { _depthStencilViewDesc.Format = Format; }
		void SetViewDimensions(D3D11_DSV_DIMENSION ViewDimension) { _depthStencilViewDesc.ViewDimension = ViewDimension; }
		void SetFlags(UINT Flags) { _depthStencilViewDesc.Flags = Flags; }

		void SetTexture1D(D3D11_TEX1D_DSV Texture1D) { _depthStencilViewDesc.Texture1D = Texture1D; }
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_DSV Texture1DArray) { _depthStencilViewDesc.Texture1DArray = Texture1DArray; }
		void SetTexture2D(D3D11_TEX2D_DSV Texture2D) { _depthStencilViewDesc.Texture2D = Texture2D; }
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_DSV Texture2DArray) { _depthStencilViewDesc.Texture2DArray = Texture2DArray; }
		void SetTexture2DMS(D3D11_TEX2DMS_DSV Texture2DMS) { _depthStencilViewDesc.Texture2DMS = Texture2DMS; }
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray) { _depthStencilViewDesc.Texture2DMSArray = Texture2DMSArray; }

		D3D11_DEPTH_STENCIL_VIEW_DESC& Get() { return _depthStencilViewDesc; }

	protected:
		D3D11_DEPTH_STENCIL_VIEW_DESC _depthStencilViewDesc;
	};

	class ShaderResourceViewDesc {
	public:
		ShaderResourceViewDesc() { SetDefaults(); }
		~ShaderResourceViewDesc() {}

		void SetDefaults();
		
		void SetFormat(DXGI_FORMAT Format) { _shaderResourceViewDesc.Format = Format; }
		void SetViewDimensions(D3D11_SRV_DIMENSION ViewDimension) { _shaderResourceViewDesc.ViewDimension = ViewDimension; }

		void SetBuffer(D3D11_BUFFER_SRV Buffer) { _shaderResourceViewDesc.Buffer = Buffer; }
		void SetTexture1D(D3D11_TEX1D_SRV Texture1D) { _shaderResourceViewDesc.Texture1D = Texture1D; }
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_SRV Texture1DArray) { _shaderResourceViewDesc.Texture1DArray = Texture1DArray; }
		void SetTexture2D(D3D11_TEX2D_SRV Texture2D) { _shaderResourceViewDesc.Texture2D = Texture2D; }
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_SRV Texture2DArray) { _shaderResourceViewDesc.Texture2DArray = Texture2DArray; }
		void SetTexture2DMS(D3D11_TEX2DMS_SRV Texture2DMS) { _shaderResourceViewDesc.Texture2DMS = Texture2DMS; }
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_SRV Texture2DMSArray) { _shaderResourceViewDesc.Texture2DMSArray = Texture2DMSArray; }
		void SetTexture3D(D3D11_TEX3D_SRV Texture3D) { _shaderResourceViewDesc.Texture3D = Texture3D; }
		void SetTexture(D3D11_TEXCUBE_SRV TextureCube) { _shaderResourceViewDesc.TextureCube = TextureCube; }
		void SetTexture(D3D11_TEXCUBE_ARRAY_SRV TextureCubeArray) { _shaderResourceViewDesc.TextureCubeArray = TextureCubeArray; }
		void SetBufferEx(D3D11_BUFFEREX_SRV BufferEx) { _shaderResourceViewDesc.BufferEx = BufferEx; }

		D3D11_SHADER_RESOURCE_VIEW_DESC& Get() { return _shaderResourceViewDesc; }

	protected:
		D3D11_SHADER_RESOURCE_VIEW_DESC _shaderResourceViewDesc;
	};

	class UnorderedAccessViewDesc {
	public:
		UnorderedAccessViewDesc() { SetDefaults(); }
		~UnorderedAccessViewDesc() {}

		void SetDefaults();

		void SetFormat(DXGI_FORMAT Format) { _unorderedAccessViewDesc.Format = Format; }
		void SetViewDimensions(D3D11_UAV_DIMENSION ViewDimension) { _unorderedAccessViewDesc.ViewDimension = ViewDimension; }

		void SetBuffer(D3D11_BUFFER_UAV Buffer) { _unorderedAccessViewDesc.Buffer = Buffer; }
		void SetTexture1D(D3D11_TEX1D_UAV Texture1D) { _unorderedAccessViewDesc.Texture1D = Texture1D; }
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_UAV Texture1DArray) { _unorderedAccessViewDesc.Texture1DArray = Texture1DArray; }
		void SetTexture2D(D3D11_TEX2D_UAV Texture2D) { _unorderedAccessViewDesc.Texture2D = Texture2D; }
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_UAV Texture2DArray) { _unorderedAccessViewDesc.Texture2DArray = Texture2DArray; }
		void SetTexture3D(D3D11_TEX3D_UAV Texture3D) { _unorderedAccessViewDesc.Texture3D = Texture3D; }

		D3D11_UNORDERED_ACCESS_VIEW_DESC& Get() { return _unorderedAccessViewDesc; }

	protected:
		D3D11_UNORDERED_ACCESS_VIEW_DESC _unorderedAccessViewDesc;
	};
}