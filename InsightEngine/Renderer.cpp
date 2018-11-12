#include "pch.h"
#include "Renderer.h"
#include "BufferConfig.h"
#include "VertexBuffer.h"

using namespace insight;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

std::shared_ptr <Renderer> Renderer::Get() {
	return _spRenderer;
}

std::shared_ptr<Resource> Renderer::CreateVertexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData) {
	
}