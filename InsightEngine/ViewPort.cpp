#include "pch.h"
#include "ViewPort.h"

using namespace insight;

ViewPort::ViewPort() {
	_viewPort.Width = 1.0f;
	_viewPort.Height = 1.0f;
	_viewPort.TopLeftX = 0.0f;
	_viewPort.TopLeftY = 0.0f;
	_viewPort.MinDepth = 0.0f;
	_viewPort.MaxDepth = 1.0f;
}

ViewPort::ViewPort(D3D11_VIEWPORT vp) {
	_viewPort = vp;
}

ViewPort::~ViewPort() {
	
}

float ViewPort::GetWidth() const {
	return _viewPort.Width;
}

float ViewPort::GetHeight() const {
	return _viewPort.Height;
}

D3D11_VIEWPORT ViewPort::Get() const{
	return _viewPort;
}