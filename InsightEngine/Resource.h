#pragma once
#include "Renderer.h"

namespace insight {
	class Resource {
	public:
		Resource();
		virtual ~Resource();

		virtual ID3D11Resource* GetResource() = 0;
		virtual ResourceType GetType() = 0;
	};
}