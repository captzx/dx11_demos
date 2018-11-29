#pragma once
#include "Application.h"
#include <string>

namespace insight {
	class EmptyApp: public Application {
	public:
		void Initialize() override;

		std::wstring GetName() override;
	};
}