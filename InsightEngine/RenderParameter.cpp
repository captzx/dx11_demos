#include "pch.h"
#include "RenderParameter.h"

using namespace insight;

#pragma region RenderParameter
RenderParameter::RenderParameter() {
	for (int i = 0; i < NUM_THREADS + 1; ++i) {
		_uiValueIDs[i] = 0;
	}
}
RenderParameter::~RenderParameter() {

}

void RenderParameter::SetName(const std::wstring& name) {
	_wsName = name;
}
std::wstring& RenderParameter::GetName() {
	return _wsName;
}

void RenderParameter::InitializeParameterData(void* pData) {
	for (int i = 0; i <= NUM_THREADS; i++)
		SetParameterData(pData, i);
}

unsigned int RenderParameter::GetValueID(unsigned int threadID) {
	return _uiValueIDs[threadID];
}
#pragma endregion

#pragma region MatrixParameter
MatrixParameter::MatrixParameter() {
	for (int i = 0; i <= NUM_THREADS; ++i) {
		XMStoreFloat4x4(&_Matrixs[i] , XMMatrixIdentity());
	}
}

MatrixParameter::~MatrixParameter() {

}

const ParameterType MatrixParameter::GetParameterType() {
	return MATRIX;
}
void MatrixParameter::SetParameterData(void* pData, unsigned int threadID) {
	if (memcmp(pData, &(_Matrixs[threadID]), sizeof(XMFLOAT4X4)) != 0) {
		++_uiValueIDs[threadID];
		_Matrixs[threadID] = *reinterpret_cast<XMFLOAT4X4*>(pData);
	}
}

XMMATRIX MatrixParameter::GetMatrix(unsigned int threadID) {
	return XMLoadFloat4x4(&_Matrixs[threadID]);
}
#pragma endregion

#pragma region ConstantBufferParameter
ConstantBufferParameter::ConstantBufferParameter() {
	for (int i = 0; i <= NUM_THREADS; ++i) _iConstBuffers[i] = -1;
}

ConstantBufferParameter::~ConstantBufferParameter() {

}

const ParameterType ConstantBufferParameter::GetParameterType() {
	return CBUFFER;
}

void ConstantBufferParameter::SetParameterData(void* pData, unsigned int theradID) {
	_iConstBuffers[theradID] = *reinterpret_cast<int*>(pData);
}

int ConstantBufferParameter::GetResourceIndex(unsigned int threadID) {
	return _iConstBuffers[threadID];
}
#pragma endregion