#include "pch.h"
#include "RasterizerStage.h"

#include "Renderer.h"
#include "ViewPort.h"

using namespace insight;
RasterizerState::RasterizerState() :
	ViewportCount(0),
	Viewports(-1),
	_pDesired(nullptr) {

	Clear();
}
RasterizerState::~RasterizerState() {

}

void RasterizerState::Clear() {
	ViewportCount.Initialize();
	Viewports.Initialize();
}
void RasterizerState::SetDesired(RasterizerState* pState) {
	_pDesired = pState;

	ViewportCount.SetDesired(&_pDesired->ViewportCount);
	Viewports.SetDesired(&_pDesired->Viewports);
}
void RasterizerState::Reset() {
	ViewportCount.Reset();
	Viewports.Reset();
}

//####

RasterizerStage::RasterizerStage() {
	DesiredState.SetDesired(&_currentState);
}
RasterizerStage::~RasterizerStage() {

}

void RasterizerStage::ClearDesiredState() {
	DesiredState.Clear();
}
void RasterizerStage::ClearCurrentState() {
	_currentState.Clear();
}
void RasterizerStage::ApplyDesiredState(ID3D11DeviceContext* pContext) {
	Renderer* pRenderer = Renderer::Get();

	int viewports = 0;
	if (DesiredState.ViewportCount.ShouldUpload() || DesiredState.Viewports.ShouldUpload()) {
		D3D11_VIEWPORT aViewPorts[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];

		for (auto i = 0; i < DesiredState.ViewportCount.Get(); ++i) {
			const ViewPort& vp = pRenderer->GetViewPort(i);

			aViewPorts[i] = vp.Get();
		}

		pContext->RSSetViewports(DesiredState.ViewportCount.Get(), aViewPorts);
	}

	//DesiredState.Reset();
	_currentState = DesiredState;
}

const RasterizerState& RasterizerStage::Get() const {
	return _currentState;
}