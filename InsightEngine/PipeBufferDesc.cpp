#include "pch.h"
#include "PipeBufferDesc.h"

using namespace insight;

void PipeBufferDesc::SetDefault() {
	_bufferDesc.ByteWidth = NULL;
	_bufferDesc.BindFlags = NULL;
	_bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_bufferDesc.CPUAccessFlags = NULL;
	_bufferDesc.MiscFlags = NULL;
	_bufferDesc.StructureByteStride = NULL;
}

void PipeBufferDesc::SetAsVertexBuffer(UINT byteWidth, bool isDynamic) {
	_bufferDesc.ByteWidth = byteWidth;
	_bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (isDynamic) {
		_bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		_bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		_bufferDesc.CPUAccessFlags = 0;
	}
}
void PipeBufferDesc::SetAsIndexBuffer(UINT byteWidth, bool isDynamic) {
	_bufferDesc.ByteWidth = byteWidth;
	_bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	if (isDynamic) {
		_bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		_bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		_bufferDesc.CPUAccessFlags = 0;
	}
}
void PipeBufferDesc::SetAsConstantBuffer(UINT byteWidth, bool isDynamic) {
	_bufferDesc.ByteWidth = byteWidth;
	_bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (isDynamic){
		_bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		_bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		_bufferDesc.CPUAccessFlags = 0;
	}
}