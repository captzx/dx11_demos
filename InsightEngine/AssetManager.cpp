#include "pch.h"
#include "AssetManager.h"

using namespace insight;

std::string _sRootDir = "./";

AssetManager::AssetManager() {

}
AssetManager::~AssetManager() {

}

std::string AssetManager::GetRootDir() {
	return _sRootDir;
}