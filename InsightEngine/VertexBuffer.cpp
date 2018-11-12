#include "pch.h"
#include "VertexBuffer.h"

using namespace insight;

VertexBuffer::VertexBuffer(std::shared_ptr<ID3D11Buffer> pBuffer) {
	_pBuffer = pBuffer;
}

VertexBuffer::~VertexBuffer() {

}

void VertexBuffer::SetVertexSize(int size) {
	_size = size;
}

void VertexBuffer::SetVertexCount(int count) {
	_count = count;
}

ResourceType VertexBuffer::GetType() {
	return RT_VERTEXBUFFER;
}