#include "pch.h"
#include "PipeBuffer.h"

#include "RenderingPipeline.h"
#include "ParameterManager.h"
#include "RenderParameter.h"

using namespace insight;

PipeBuffer::PipeBuffer() {
	ZeroMemory(&_DesiredDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&_ActualDesc, sizeof(D3D11_BUFFER_DESC));
}

D3D11_BUFFER_DESC PipeBuffer::GetActualDescription() {
	ZeroMemory(&_ActualDesc, sizeof(D3D11_BUFFER_DESC));

	if (_pBuffer)
		_pBuffer->GetDesc(&_ActualDesc);

	return(_ActualDesc);
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
	_Mappings.push_back(mapping);
}
void ConstantBuffer::EmptyMappings() {
	_Mappings.clear();
}
void ConstantBuffer::EvaluateMappings(RenderingPipeline* pPipeline, IParameterManager* pParameterManager) {
	if (_pBuffer) {
		if (GetAutoUpdate()) {
			bool doUpdate = false;

			for (size_t i = 0; i < _Mappings.size(); ++i) {
				if (_Mappings[i].pParameter->GetValueID(pParameterManager->GetID())!=_Mappings[i].valueID) {
					doUpdate = true;
					break;
				}
			}

			if (doUpdate) {
				D3D11_MAPPED_SUBRESOURCE mappedResource = pPipeline->MapResource(this, 0, D3D11_MAP_WRITE_DISCARD, 0);

				for (size_t i = 0; i < _Mappings.size(); ++i) {
					RenderParameter* pParameter = _Mappings[i].pParameter;
					auto offset = _Mappings[i].offset;
					auto size = _Mappings[i].size;
					auto elements = _Mappings[i].elements;
					auto valueID = _Mappings[i].valueID;
					auto threadID = pParameterManager->GetID();

					_Mappings[i].valueID = pParameter->GetValueID(threadID);

					if (_Mappings[i].varclass == D3D_SVC_VECTOR) {

					}
					else if (_Mappings[i].varclass == D3D_SVC_MATRIX_ROWS || _Mappings[i].varclass == D3D_SVC_MATRIX_COLUMNS) {
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