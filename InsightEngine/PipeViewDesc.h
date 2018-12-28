#pragma once

namespace insight {
	class RenderTargetViewDesc {
	public:
		RenderTargetViewDesc() { SetDefaults(); }
		~RenderTargetViewDesc() {}

		void SetDefaults();

		void SetFormat(DXGI_FORMAT Format) { _rtvDesc.Format = Format; }
		void SetViewDimension(D3D11_RTV_DIMENSION ViewDimension) { _rtvDesc.ViewDimension; }

		void SetBuffer(D3D11_BUFFER_RTV Buffer) { _rtvDesc.Buffer = Buffer; }
		void SetTexture1D(D3D11_TEX1D_RTV Texture1D) { _rtvDesc.Texture1D = Texture1D; }
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_RTV Texture1DArray) { _rtvDesc.Texture1DArray = Texture1DArray; }
		void SetTexture2D(D3D11_TEX2D_RTV Texture2D) { _rtvDesc.Texture2D = Texture2D; }
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_RTV Texture2DArray) { _rtvDesc.Texture2DArray = Texture2DArray; }
		void SetTexture2DMS(D3D11_TEX2DMS_RTV Texture2DMS) { _rtvDesc.Texture2DMS = Texture2DMS; }
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_RTV Texture2DMSArray) { _rtvDesc.Texture2DMSArray = Texture2DMSArray; }
		void SetTexture3D(D3D11_TEX3D_RTV Texture3D) { _rtvDesc.Texture3D = Texture3D; }

		D3D11_RENDER_TARGET_VIEW_DESC Get() { return _rtvDesc; }
	protected:
		D3D11_RENDER_TARGET_VIEW_DESC _rtvDesc;
	};

	class DepthStencilViewDesc{
	public:
		DepthStencilViewDesc() { SetDefaults(); }
		~DepthStencilViewDesc() {}

		void SetDefaults();

		void SetFormat(DXGI_FORMAT Format) { _dsvDesc.Format = Format; }
		void SetViewDimensions(D3D11_DSV_DIMENSION ViewDimension) { _dsvDesc.ViewDimension = ViewDimension; }
		void SetFlags(UINT Flags) { _dsvDesc.Flags = Flags; }

		void SetTexture1D(D3D11_TEX1D_DSV Texture1D) { _dsvDesc.Texture1D = Texture1D; }
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_DSV Texture1DArray) { _dsvDesc.Texture1DArray = Texture1DArray; }
		void SetTexture2D(D3D11_TEX2D_DSV Texture2D) { _dsvDesc.Texture2D = Texture2D; }
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_DSV Texture2DArray) { _dsvDesc.Texture2DArray = Texture2DArray; }
		void SetTexture2DMS(D3D11_TEX2DMS_DSV Texture2DMS) { _dsvDesc.Texture2DMS = Texture2DMS; }
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray) { _dsvDesc.Texture2DMSArray = Texture2DMSArray; }

		D3D11_DEPTH_STENCIL_VIEW_DESC& Get() { return _dsvDesc; }

	protected:
		D3D11_DEPTH_STENCIL_VIEW_DESC _dsvDesc;
	};

	class ShaderResourceViewDesc {
	public:
		ShaderResourceViewDesc() { SetDefaults(); }
		~ShaderResourceViewDesc() {}

		void SetDefaults();
		
		void SetFormat(DXGI_FORMAT Format) { _srvDesc.Format = Format; }
		void SetViewDimensions(D3D11_SRV_DIMENSION ViewDimension) { _srvDesc.ViewDimension = ViewDimension; }

		void SetBuffer(D3D11_BUFFER_SRV Buffer) { _srvDesc.Buffer = Buffer; }
		void SetTexture1D(D3D11_TEX1D_SRV Texture1D) { _srvDesc.Texture1D = Texture1D; }
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_SRV Texture1DArray) { _srvDesc.Texture1DArray = Texture1DArray; }
		void SetTexture2D(D3D11_TEX2D_SRV Texture2D) { _srvDesc.Texture2D = Texture2D; }
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_SRV Texture2DArray) { _srvDesc.Texture2DArray = Texture2DArray; }
		void SetTexture2DMS(D3D11_TEX2DMS_SRV Texture2DMS) { _srvDesc.Texture2DMS = Texture2DMS; }
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_SRV Texture2DMSArray) { _srvDesc.Texture2DMSArray = Texture2DMSArray; }
		void SetTexture3D(D3D11_TEX3D_SRV Texture3D) { _srvDesc.Texture3D = Texture3D; }
		void SetTexture(D3D11_TEXCUBE_SRV TextureCube) { _srvDesc.TextureCube = TextureCube; }
		void SetTexture(D3D11_TEXCUBE_ARRAY_SRV TextureCubeArray) { _srvDesc.TextureCubeArray = TextureCubeArray; }
		void SetBufferEx(D3D11_BUFFEREX_SRV BufferEx) { _srvDesc.BufferEx = BufferEx; }

		D3D11_SHADER_RESOURCE_VIEW_DESC& Get() { return _srvDesc; }

	protected:
		D3D11_SHADER_RESOURCE_VIEW_DESC _srvDesc;
	};

	class UnorderedAccessViewDesc {
	public:
		UnorderedAccessViewDesc() { SetDefaults(); }
		~UnorderedAccessViewDesc() {}

		void SetDefaults();

		void SetFormat(DXGI_FORMAT Format) { _uavDesc.Format = Format; }
		void SetViewDimensions(D3D11_UAV_DIMENSION ViewDimension) { _uavDesc.ViewDimension = ViewDimension; }

		void SetBuffer(D3D11_BUFFER_UAV Buffer) { _uavDesc.Buffer = Buffer; }
		void SetTexture1D(D3D11_TEX1D_UAV Texture1D) { _uavDesc.Texture1D = Texture1D; }
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_UAV Texture1DArray) { _uavDesc.Texture1DArray = Texture1DArray; }
		void SetTexture2D(D3D11_TEX2D_UAV Texture2D) { _uavDesc.Texture2D = Texture2D; }
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_UAV Texture2DArray) { _uavDesc.Texture2DArray = Texture2DArray; }
		void SetTexture3D(D3D11_TEX3D_UAV Texture3D) { _uavDesc.Texture3D = Texture3D; }

		D3D11_UNORDERED_ACCESS_VIEW_DESC& Get() { return _uavDesc; }

	protected:
		D3D11_UNORDERED_ACCESS_VIEW_DESC _uavDesc;
	};
}