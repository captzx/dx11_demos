#include "pch.h"
#include "OutputMergerStage.h"
#include "Renderer.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"

using namespace insight;

OutputMergerStage::OutputMergerStage() {
	_desiredState.SetRefState(&_currentState);
}
OutputMergerStage::~OutputMergerStage() {

}


void OutputMergerStage::SetFeatureLevel(D3D_FEATURE_LEVEL level) {
	_featureLevel = level;
	_currentState.SetFeatureLevel(level);
	_desiredState.SetFeatureLevel(level);
}


void OutputMergerStage::ClearDesiredState() {
	_desiredState.ClearState();
}

void OutputMergerStage::ClearCurrentState() {
	_currentState.ClearState();
}

void OutputMergerStage::ApplyDesiredRenderTargetStates(ID3D11DeviceContext* pContext) {
	int iRTVCount = 0;
	int iUAVCount = 0;
	
	if (_desiredState.RenderTargetViews.IsNeedUpload() || _desiredState.DepthStencilViews.IsNeedUpdate()) {
		std::shared_ptr<Renderer> pRenderer = Renderer::Get();

		ID3D11RenderTargetView*	RTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
		ID3D11UnorderedAccessView* UAVs[D3D11_PS_CS_UAV_REGISTER_COUNT];
		ID3D11DepthStencilView* DSV = 0;

		for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
			RenderTargetView& rtv = pRenderer->GetRenderTargetViewByIndex(_desiredState.RenderTargetViews.GetState(i));
			RTVs[i] = rtv.Get();
		
			if (RTVs[i] != nullptr) {
				iRTVCount = i + 1;
			}
		}

		for (int i = 0; i < D3D11_PS_CS_UAV_REGISTER_COMPONENTS; ++i) {

		}

		DepthStencilView& dsv = pRenderer->GetDepthStencilViewByIndex(_desiredState.DepthStencilViews.GetState());
		DSV = dsv.Get();

		pContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, RTVs, DSV);

		for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
			_currentState.RenderTargetViews.SetState(i, _desiredState.RenderTargetViews.GetState(i));
		}

		for (int i = 0; i < D3D11_PS_CS_UAV_REGISTER_COUNT; i++) {
			/*_currentState.UnorderedAccessViews.SetState(i, _desiredState.UnorderedAccessViews.GetState(i));
			_currentState.UAVInitialCounts.SetState(i, _desiredState.UAVInitialCounts.GetState(i));*/
		}

		_currentState.DepthStencilViews.SetState(_desiredState.DepthStencilViews.GetState());

		/*_desiredState.RenderTargetViews.ResetTracking();
		_desiredState.UnorderedAccessViews.ResetTracking();
		_desiredState.UAVInitialCounts.ResetTracking();
		_desiredState.DepthTargetViews.ResetTracking();*/
	}

}

void OutputMergerStage::ApplyDesiredBlendAndDepthStencilStates(ID3D11DeviceContext* pContext) {

}

void OutputMergerStage::ApplyDesiredState(ID3D11DeviceContext* pContext) {
	ApplyDesiredRenderTargetStates(pContext);
	ApplyDesiredBlendAndDepthStencilStates(pContext);
}


const OutputMergerStageState& OutputMergerStage::GetCurrentState() const {
	return _currentState;
}
