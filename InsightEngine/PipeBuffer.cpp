#include "pch.h"
#include "PipeBuffer.h"

#include "RenderingPipeline.h"

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

}
void ConstantBuffer::EmptyMappings() {

}
void ConstantBuffer::EvaluateMappings(RenderingPipeline* pPipeline, IParameterManager* pParamManager) {

}
bool ConstantBuffer::ContainsMapping(int index, const ConstantBufferMapping& mapping) {

}

void ConstantBuffer::SetAutoUpdate(bool enable) {

}
bool ConstantBuffer::GetAutoUpdate() {

}
#pragma endregion