#pragma once

namespace insight {
	class Asset {
	public:
		Asset(std::string assetName);
		virtual ~Asset();

		bool Load();
		char* GetRawData();
		size_t GetSize();

	private:
		std::string _sName;
		char* _cRawData;
		size_t _size;
	};
}
