#pragma once

namespace insight {
	class Texture1dDesc{
	public:
		Texture1dDesc() { SetDefaults(); }
		~Texture1dDesc() {}

		void SetDefaults();

		void SetWidth(UINT Width) { _t1dDesc.Width = Width; }
		void SetMipLevels(UINT MipLevels) { _t1dDesc.MipLevels = MipLevels; }
		void SetArraySize(UINT ArraySize) { _t1dDesc.ArraySize = ArraySize; }
		void SetFormat(DXGI_FORMAT Format) { _t1dDesc.Format = Format; }
		void SetUsage(D3D11_USAGE Usage) { _t1dDesc.Usage = Usage; }
		void SetBindFlags(UINT BindFlags) { _t1dDesc.BindFlags = BindFlags; }
		void SetCPUAccessFlags(UINT CPUAccessFlags) { _t1dDesc.CPUAccessFlags = CPUAccessFlags; }
		void SetMiscFlags(UINT MiscFlags) { _t1dDesc.MiscFlags = MiscFlags; }

		D3D11_TEXTURE1D_DESC Get() { return _t1dDesc; }
	private:
		D3D11_TEXTURE1D_DESC _t1dDesc;
	
	};

	class Texture2dDesc {
	public:
		Texture2dDesc() { SetDefaults(); }
		~Texture2dDesc() {}

		void SetDefaults();
		void SetDepthBuffer(UINT width, UINT height);
		void SetColorBuffer(UINT width, UINT height);

		void SetWidth(UINT Width) { _t2dDesc.Width = Width; }
		void SetHeight(UINT Height) { _t2dDesc.Height = Height; }
		void SetMipLevels(UINT MipLevels) { _t2dDesc.MipLevels = MipLevels; }
		void SetArraySize(UINT ArraySize) { _t2dDesc.ArraySize = ArraySize; }
		void SetFormat(DXGI_FORMAT Format) { _t2dDesc.Format = Format; }
		void SetFormat(DXGI_SAMPLE_DESC SampleDesc) { _t2dDesc.SampleDesc = SampleDesc; }
		void SetUsage(D3D11_USAGE Usage) { _t2dDesc.Usage = Usage; }
		void SetBindFlags(UINT BindFlags) { _t2dDesc.BindFlags = BindFlags; }
		void SetCPUAccessFlags(UINT CPUAccessFlags) { _t2dDesc.CPUAccessFlags = CPUAccessFlags; }
		void SetMiscFlags(UINT MiscFlags) { _t2dDesc.MiscFlags = MiscFlags; }

		D3D11_TEXTURE2D_DESC& Get() { return _t2dDesc; }
	private:
		D3D11_TEXTURE2D_DESC _t2dDesc;
	};

	class Texture3dDesc {
	public:
		Texture3dDesc() { SetDefaults(); }
		~Texture3dDesc() {}

		void SetDefaults();

		void SetWidth(UINT Width) { _t3dDesc.Width = Width; }
		void SetHeight(UINT Height) { _t3dDesc.Height = Height; }
		void SetDepth(UINT Depth) { _t3dDesc.Depth = Depth; }
		void SetMipLevels(UINT MipLevels) { _t3dDesc.MipLevels = MipLevels; }
		void SetFormat(DXGI_FORMAT Format) { _t3dDesc.Format = Format; }
		void SetUsage(D3D11_USAGE Usage) { _t3dDesc.Usage = Usage; }
		void SetBindFlags(UINT BindFlags) { _t3dDesc.BindFlags = BindFlags; }
		void SetCPUAccessFlags(UINT CPUAccessFlags) { _t3dDesc.CPUAccessFlags = CPUAccessFlags; }
		void SetMiscFlags(UINT MiscFlags) { _t3dDesc.MiscFlags = MiscFlags; }

		D3D11_TEXTURE3D_DESC Get() { return _t3dDesc; }
	private:
		D3D11_TEXTURE3D_DESC _t3dDesc;
	};
}