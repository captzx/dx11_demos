#include "pch.h"
#include "OutputMergerStage.h"

#include "Renderer.h"
#include "PipeView.h"

using namespace insight;

OutputMergerState::OutputMergerState() :
	DepthStencilState(-1),
	RenderTargetViews(0),
	DepthTargetViews(0),
	_pDesiredState(nullptr) {

	ClearState();
}
OutputMergerState::~OutputMergerState() {

}

void OutputMergerState::ClearState() {
	DepthStencilState.Initialize();
	RenderTargetViews.Initialize();
	DepthTargetViews.Initialize();
}
void OutputMergerState::SetDesiredState(OutputMergerState* pState) {
	_pDesiredState = pState;

	DepthStencilState.SetDesired(&_pDesiredState->DepthStencilState);
	RenderTargetViews.SetDesired(&_pDesiredState->RenderTargetViews);
	DepthTargetViews.SetDesired(&_pDesiredState->DepthTargetViews);
}
void OutputMergerState::ResetUpdateFlags() {
	DepthStencilState.Reset();
	RenderTargetViews.Reset();
	DepthTargetViews.Reset();
}
int OutputMergerState::GetRenderTargetCount() const {
	unsigned int count = 0;

	for (unsigned int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
	{
		if (RenderTargetViews.Get(i) != -1)
			count++;
	}

	return(count);
}



//#############################################


OutputMergerStage::OutputMergerStage() {
	DesiredState.SetDesiredState(&_currentState);
}
OutputMergerStage::~OutputMergerStage() {

}
void OutputMergerStage::ClearDesiredState() {
	DesiredState.ClearState();
}
void OutputMergerStage::ClearCurrentState() {
	_currentState.ClearState();
}
void OutputMergerStage::ApplyDesiredRenderTargetStates(ID3D11DeviceContext* pContext) {
	int rtvCount = 0;
	int uavCount = 0;

	if (DesiredState.RenderTargetViews.ShouldUpload() || DesiredState.DepthTargetViews.ShouldUpload()||true) {

		Renderer* pRenderer = Renderer::Get();

		ID3D11RenderTargetView*	rtvs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
		ID3D11DepthStencilView* dsv = 0;

		for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {

			RenderTargetView rtv = pRenderer->GetRenderTargetViewByIndex(DesiredState.RenderTargetViews.Get(i));
			rtvs[i] = rtv.Get();

			if (rtvs[i] != nullptr) {
				rtvCount = i + 1; // Record the number of non-null rtvs...
			}
		}

		DepthStencilView& DSV = pRenderer->GetDepthStencilViewByIndex(DesiredState.DepthTargetViews.Get());
		dsv = DSV.Get();

		// TODO: convert this to bind the UAVs too...
		pContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, rtvs, dsv);
		//pContext->OMSetRenderTargetsAndUnorderedAccessViews( rtvCount, rtvs, dsv, 
		//	rtvCount, uavCount, uavs, (UINT*)&DesiredState.UAVInitialCounts );

		// TODO: Find a better way to copy the state from desired to current...

		for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
			_currentState.RenderTargetViews.Set(i, DesiredState.RenderTargetViews.Get(i));
		}


		_currentState.DepthTargetViews.Set(DesiredState.DepthTargetViews.Get());

		DesiredState.RenderTargetViews.Reset();
		
		DesiredState.DepthTargetViews.Reset();
	}
}
void OutputMergerStage::ApplyDesiredBlendAndDepthStencilStates(ID3D11DeviceContext* pContext) {

}
void OutputMergerStage::ApplyDesiredState(ID3D11DeviceContext* pContext) {
	ApplyDesiredRenderTargetStates(pContext);
	ApplyDesiredBlendAndDepthStencilStates(pContext);
}

const OutputMergerState& OutputMergerStage::GetCurrentState() const {
	return _currentState;
}