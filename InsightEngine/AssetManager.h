#pragma once

namespace insight {
	class AssetManager {
	public:
		~AssetManager();
		static std::string GetRootDir();

	private:
		AssetManager();
		static std::string _sRootDir;
	};
}