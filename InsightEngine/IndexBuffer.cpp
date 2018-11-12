#include "pch.h"
#include "IndexBuffer.h"

using namespace insight;

IndexBuffer::IndexBuffer(std::shared_ptr<ID3D11Buffer> pBuffer) {
	_pBuffer = pBuffer;
}

IndexBuffer::~IndexBuffer() {

}

void IndexBuffer::SetIndexSize(int size) {
	_size = size;
}

void IndexBuffer::SetIndexCount(int count) {
	_count = count;
}

ResourceType IndexBuffer::GetType() {
	return RT_INDEXBUFFER;
}