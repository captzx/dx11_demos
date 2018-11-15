#include "pch.h"
#include "Buffer.h"

using namespace insight;

Buffer::Buffer() {
	ZeroMemory(&_desiredDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&_actualDesc, sizeof(D3D11_BUFFER_DESC));
}

Buffer::~Buffer() {

}

D3D11_BUFFER_DESC Buffer::GetActualDescription() {
	ZeroMemory(&_actualDesc, sizeof(D3D11_BUFFER_DESC));

	if (_pBuffer)
		_pBuffer->GetDesc(&_actualDesc);

	return _actualDesc;
}

D3D11_BUFFER_DESC Buffer::GetDesiredDescription() {
	return _desiredDesc;
}

void Buffer::SetDesiredDescription(D3D11_BUFFER_DESC desc) {
	_desiredDesc = desc;
}

UINT Buffer::GetByteWidth() {
	return _desiredDesc.ByteWidth;
}

void Buffer::SetByteWidht(UINT byteWidth) {
	_desiredDesc.ByteWidth = byteWidth;

}

D3D11_USAGE Buffer::GetUsage() {
	return _desiredDesc.Usage;
}

void Buffer::SetUsage(D3D11_USAGE usage) {
	_desiredDesc.Usage = usage;
}

UINT Buffer::GetBindFlags() {
	return _desiredDesc.BindFlags;
}

void Buffer::SetBindFlags(UINT bindFlags) {
	_desiredDesc.BindFlags = bindFlags;
}

UINT Buffer::GetCPUAccessFlags() {
	return _desiredDesc.CPUAccessFlags;
}

void Buffer::SetCPUAccessFlags(UINT CPUAccessFlags) {
	_desiredDesc.CPUAccessFlags = CPUAccessFlags;
}

UINT Buffer::GetMiscFlags() {
	return _desiredDesc.MiscFlags;
}

void Buffer::SetMiscFlags(UINT miscFlags) {
	_desiredDesc.MiscFlags = miscFlags;
}

UINT Buffer::GetStructureByteStride() {
	return _desiredDesc.StructureByteStride;
}

void Buffer::SetStructrueByteStride(UINT structureByteStride) {
	_desiredDesc.StructureByteStride = structureByteStride;
}

void* Buffer::Map() {
	return nullptr;
}

void Buffer::UnMap() {

}

ID3D11Buffer* Buffer::GetResource() {
	return _pBuffer;
}