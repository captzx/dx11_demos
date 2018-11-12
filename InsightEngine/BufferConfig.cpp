#include "pch.h"
#include "BufferConfig.h"

using namespace insight;

BufferConfig::BufferConfig(){
	SetDefaults();
}

BufferConfig::~BufferConfig() {

}

void BufferConfig::SetDefaults() {
	_state.ByteWidth = 1;
	_state.Usage = D3D11_USAGE_DEFAULT;
	_state.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_state.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_state.MiscFlags = 0;
	_state.StructureByteStride = 0;
}

void BufferConfig::SetDefaultConstantBuffer(UINT byteWidth, bool isDynamic) {
	_state.ByteWidth = byteWidth;
	_state.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_state.MiscFlags = 0;
	_state.StructureByteStride = 0;
	if (isDynamic) {
		_state.Usage = D3D11_USAGE_DYNAMIC;
		_state.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_state.Usage = D3D11_USAGE_IMMUTABLE;
		_state.CPUAccessFlags = 0;
	}
}

void BufferConfig::SetDefaultVertexBuffer(UINT byteWidth, bool isDynamic) {
	_state.ByteWidth = byteWidth;
	_state.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_state.MiscFlags = 0;
	_state.StructureByteStride = 0;
	if (isDynamic) {
		_state.Usage = D3D11_USAGE_DYNAMIC;
		_state.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_state.Usage = D3D11_USAGE_IMMUTABLE;
		_state.CPUAccessFlags = 0;
	}
}

void BufferConfig::SetDefaultIndexBuffer(UINT byteWidth, bool isDynamic) {
	_state.ByteWidth = byteWidth;
	_state.BindFlags = D3D11_BIND_INDEX_BUFFER;
	_state.MiscFlags = 0;
	_state.StructureByteStride = 0;
	if (isDynamic) {
		_state.Usage = D3D11_USAGE_DYNAMIC;
		_state.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else {
		_state.Usage = D3D11_USAGE_IMMUTABLE;
		_state.CPUAccessFlags = 0;
	}
}

void BufferConfig::SetByteWidht(UINT byteWidth) {
	_state.ByteWidth = byteWidth;
}

void BufferConfig::SetUsage(D3D11_USAGE usage) {
	_state.Usage = usage;
}

void BufferConfig::SetBindFlags(UINT bindFlags) {
	_state.BindFlags = bindFlags;
}

void BufferConfig::SetCPUAccessFlags(UINT CPUAccessFlags) {
	_state.CPUAccessFlags = CPUAccessFlags;
}

void BufferConfig::SetMiscFlags(UINT miscFlags) {
	_state.MiscFlags = miscFlags;
}

void BufferConfig::SetStructrueByteStride(UINT structureByteStride) {
	_state.StructureByteStride = structureByteStride;
}

D3D11_BUFFER_DESC BufferConfig::GetBufferDesc() {
	return _state;
}
