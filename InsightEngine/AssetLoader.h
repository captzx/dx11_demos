#pragma once

namespace insight {
	class Asset;
	class AssetLoader {
	public:
		AssetLoader();
		virtual ~AssetLoader();

		void Load(Asset* asset);
	};
}