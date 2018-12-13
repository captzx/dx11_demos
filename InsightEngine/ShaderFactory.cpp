#include "pch.h"
#include "ShaderFactory.h"
//#include "AssetManager.h"
//#include "Asset.h"
//
//using namespace insight;
//
//ShaderFactory::ShaderFactory() {
//
//}
//
//ShaderFactory::~ShaderFactory() {
//
//}
//
////ID3DBlob* ShaderFactory::GenerateShader(ShaderType type, std::string& filename, std::string& function, std::string& model, const D3D_SHADER_MACRO* pDefines, bool enablelogging = true) {
////	HRESULT hr = S_OK;
////
////	UINT flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
////#ifdef _DEBUG
////	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION; // | D3DCOMPILE_WARNINGS_ARE_ERRORS;
////#endif
////
////	std::string filepath = AssetManager::GetRootDir() + filename;
////
////	// Load the file into memory
////
////	Asset SourceFile(filepath);
////	if (!SourceFile.Load()) {
////		return(nullptr);
////	}
////
////	ID3DBlob* pCompiledShader = nullptr;
////	ID3DBlob* pErrorMessages = nullptr;
////	if (FAILED(hr = D3DCompile(SourceFile.GetRawData(), SourceFile.GetSize(), nullptr, pDefines, nullptr, function.c_str(), model.c_str(), flags, 0,
////		&pCompiledShader, &pErrorMessages))) {
////
////	}
////
////	return pCompiledShader;
////}