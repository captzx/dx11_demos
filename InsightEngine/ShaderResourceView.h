#pragma once

namespace insight {
	class ShaderResourceView {
	public:
		ShaderResourceView(std::shared_ptr<ShaderResourceView> pViewConfig);
		~ShaderResourceView();

		ID3D11ShaderResourceView* GetSRV();

	protected:
		std::shared_ptr<ID3D11ShaderResourceView> _pShaderResourceView;
	};
}