#include "pch.h"
#include "ViewPort.h"

using namespace insight;

ViewPort::ViewPort() {
	_vp.Width = 1.0f;
	_vp.Height = 1.0f;
	_vp.TopLeftX = 0.0f;
	_vp.TopLeftY = 0.0f;
	_vp.MinDepth = 0.0f;
	_vp.MaxDepth = 1.0f;
}

ViewPort::ViewPort(D3D11_VIEWPORT vp) {
	_vp = vp;
}

ViewPort::~ViewPort() {
	
}

float ViewPort::GetWidth() const {
	return _vp.Width;
}

float ViewPort::GetHeight() const {
	return _vp.Height;
}

D3D11_VIEWPORT ViewPort::Get() const{
	return _vp;
}