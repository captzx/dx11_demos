#include "pch.h"
#include "PipeBuffer.h"

#include "RenderingPipeline.h"
#include "ParameterManager.h"
#include "RenderParameter.h"

using namespace insight;

PipeBuffer::PipeBuffer() {
	ZeroMemory(&_desiredDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&_actualDesc, sizeof(D3D11_BUFFER_DESC));
}

D3D11_BUFFER_DESC PipeBuffer::GetActualDescription() {
	ZeroMemory(&_actualDesc, sizeof(D3D11_BUFFER_DESC));

	if (_pBuffer)
		_pBuffer->GetDesc(&_actualDesc);

	return(_actualDesc);
}

UINT PipeBuffer::GetByteWidth(){
	D3D11_BUFFER_DESC description = GetActualDescription();

	return description.ByteWidth;
}

D3D11_USAGE PipeBuffer::GetUsage(){
	D3D11_BUFFER_DESC description = GetActualDescription();

	return description.Usage;
}

UINT PipeBuffer::GetBindFlags(){
	D3D11_BUFFER_DESC description = GetActualDescription();

	return description.BindFlags;
}

UINT PipeBuffer::GetCPUAccessFlags(){
	D3D11_BUFFER_DESC description = GetActualDescription();

	return description.CPUAccessFlags;
}

UINT PipeBuffer::GetMiscFlags(){
	D3D11_BUFFER_DESC description = GetActualDescription();

	return description.MiscFlags;
}

UINT PipeBuffer::GetStructureByteStride() {
	D3D11_BUFFER_DESC description = GetActualDescription();

	return description.StructureByteStride;
}

#pragma region ConstantBuffer
void ConstantBuffer::AddMapping(ConstantBufferMapping& mapping) {
	_vConstantBufferMappings.push_back(mapping);
}
void ConstantBuffer::EmptyMappings() {
	_vConstantBufferMappings.clear();
}
void ConstantBuffer::EvaluateMappings(RenderingPipeline* pPipeline, IParameterManager* pParameterManager) {
	if (_pBuffer) {
		if (GetAutoUpdate()) {
			bool doUpdate = false;

			for (size_t i = 0; i < _vConstantBufferMappings.size(); ++i) {
				if (_vConstantBufferMappings[i].pParameter->GetValueID(pParameterManager->GetID())!=_vConstantBufferMappings[i].ValueID) {
					doUpdate = true;
					break;
				}
			}

			if (doUpdate) {
				D3D11_MAPPED_SUBRESOURCE mappedResource = pPipeline->MapResource(this, 0, D3D11_MAP_WRITE_DISCARD, 0);

				for (size_t i = 0; i < _vConstantBufferMappings.size(); ++i) {
					RenderParameter* pParameter = _vConstantBufferMappings[i].pParameter;
					auto offset = _vConstantBufferMappings[i].Offset;
					auto size = _vConstantBufferMappings[i].Size;
					auto elements = _vConstantBufferMappings[i].Elements;
					auto valueID = _vConstantBufferMappings[i].ValueID;
					auto threadID = pParameterManager->GetID();

					_vConstantBufferMappings[i].ValueID = pParameter->GetValueID(threadID);

					if (_vConstantBufferMappings[i].VariableClass == D3D_SVC_VECTOR) {

					}
					else if (_vConstantBufferMappings[i].VariableClass == D3D_SVC_MATRIX_ROWS || _vConstantBufferMappings[i].VariableClass == D3D_SVC_MATRIX_COLUMNS) {
						if (elements == 0) {
							XMMATRIX matrix = pParameterManager->GetMatrixParameter(pParameter);
							XMMATRIX* pBuffer = reinterpret_cast<XMMATRIX*>((char*)mappedResource.pData + offset);		// 在这里修改了mappedResource里的内容
							*pBuffer = matrix;
						}
						else {
							if (size == elements * sizeof(XMMATRIX)) {

							}
						}
					}
				}

				pPipeline->UnMapResource(this, 0);
			}
		}
	}
}
bool ConstantBuffer::ContainsMapping(int index, const ConstantBufferMapping& mapping) {
	return true;
}

void ConstantBuffer::SetAutoUpdate(bool enable) {
	_bAutoUpdate = enable;
}
bool ConstantBuffer::GetAutoUpdate() {
	return _bAutoUpdate;
}
#pragma endregion