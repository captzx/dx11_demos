#pragma once

namespace insight {
	class ViewPort {
	public:
		ViewPort();
		ViewPort(D3D11_VIEWPORT viewport);
		~ViewPort();

		float GetWidth() const;
		float GetHeight() const;
		/*Vector2f GetClipSpacePosition(const Vector2f& screen) const;
		Vector2f GetScreenSpacePosition(const Vector2f& clip) const;*/

	protected:
		D3D11_VIEWPORT			_viewPort;
	};
}