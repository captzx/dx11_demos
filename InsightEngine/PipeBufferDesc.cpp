#include "pch.h"
#include "PipeBufferDesc.h"

using namespace insight;

void PipeBufferDesc::SetDefault() {
	_bd.ByteWidth = NULL;
	_bd.BindFlags = NULL;
	_bd.Usage = D3D11_USAGE_DEFAULT;
	_bd.CPUAccessFlags = NULL;
	_bd.MiscFlags = NULL;
	_bd.StructureByteStride = NULL;
}

void PipeBufferDesc::SetAsVertexBuffer(UINT byteWidth, bool isDynamic) {
	_bd.ByteWidth = byteWidth;
	_bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (isDynamic) {
		_bd.Usage = D3D11_USAGE_DYNAMIC;
		_bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_bd.Usage = D3D11_USAGE_IMMUTABLE;
		_bd.CPUAccessFlags = 0;
	}
}
void PipeBufferDesc::SetAsIndexBuffer(UINT byteWidth, bool isDynamic) {
	_bd.ByteWidth = byteWidth;
	_bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	if (isDynamic) {
		_bd.Usage = D3D11_USAGE_DYNAMIC;
		_bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_bd.Usage = D3D11_USAGE_IMMUTABLE;
		_bd.CPUAccessFlags = 0;
	}
}
void PipeBufferDesc::SetAsConstantBuffer(UINT byteWidth, bool isDynamic) {
	_bd.ByteWidth = byteWidth;
	_bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (isDynamic){
		_bd.Usage = D3D11_USAGE_DYNAMIC;
		_bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_bd.Usage = D3D11_USAGE_IMMUTABLE;
		_bd.CPUAccessFlags = 0;
	}
}