#include "pch.h"
#include "OutputMergerStageState.h"

using namespace insight;

OutputMergerStageState::OutputMergerStageState():
	RenderTargetViews(0),
	DepthStencilViews(0){

	ClearState();
}
OutputMergerStageState::~OutputMergerStageState() {

}


void OutputMergerStageState::SetFeatureLevel(D3D_FEATURE_LEVEL level) {
	_featureLevel = level;
}

void OutputMergerStageState::ClearState() {
	RenderTargetViews.InitializeStates();
	DepthStencilViews.InitializeState();
}

void OutputMergerStageState::SetRefState(OutputMergerStageState* pState) {
	_pRefState = pState;

	RenderTargetViews.SetDesiredState(&_pRefState->RenderTargetViews);
	DepthStencilViews.SetDesiredState(&_pRefState->DepthStencilViews);
}

void OutputMergerStageState::ResetUpdateFlags() {
	RenderTargetViews.ResetUploadFlags();
	DepthStencilViews.ResetUploadFlag();
}


int OutputMergerStageState::GetRenderTargetCount() const {
	unsigned int count = 0;

	for (unsigned int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
		if (RenderTargetViews.GetState(i) != -1) {
			++count;
		}
	}
	
	return count;
}
