#pragma once

class Asset;
namespace insight {
	class AssetLoader {
	public:
		AssetLoader();
		virtual ~AssetLoader();

		void Load(Asset* asset);
	};
}