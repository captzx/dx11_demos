#pragma once

namespace insight {
	class ViewPort {
	public:
		ViewPort();
		ViewPort(D3D11_VIEWPORT vp);
		~ViewPort();

		float GetWidth() const;
		float GetHeight() const;

		D3D11_VIEWPORT Get() const;
	protected:
		D3D11_VIEWPORT _viewPort;
	};
}