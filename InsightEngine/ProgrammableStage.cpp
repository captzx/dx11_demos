#include "pch.h"
#include "ProgrammableStage.h"

using namespace insight;

ProgrammableStageState::ProgrammableStageState() :
	ShaderProgram(-1),
	_pDesiredState(nullptr),
	ConstantBuffers(nullptr){

	Clear();
}

ProgrammableStageState::~ProgrammableStageState(){

}

void ProgrammableStageState::Clear(){
	ShaderProgram.Initialize();
}

void ProgrammableStageState::SetDesired(ProgrammableStageState* pState){
	_pDesiredState = pState;

	ShaderProgram.SetDesired(&_pDesiredState->ShaderProgram);
	ConstantBuffers.SetDesired(&_pDesiredState->ConstantBuffers);
	//....
}

void ProgrammableStageState::Reset(){
	ShaderProgram.Reset();
	
}

//####

ProgrammableStage::ProgrammableStage() {
	DesiredState.SetDesired(&_currentState);
}
ProgrammableStage::~ProgrammableStage() {

}

void ProgrammableStage::ClearDesiredState() {
	DesiredState.Clear();
}
void ProgrammableStage::ClearCurrentState() {
	_currentState.Clear();
}
void ProgrammableStage::ApplyDesiredState(ID3D11DeviceContext* pContext) {
	if (DesiredState.ShaderProgram.ShouldUpload()) {
		BindShaderProgram(pContext);
	}

	if (DesiredState.ConstantBuffers.ShouldUpload()) {
		BindConstantBuffers(pContext, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1);
	}

	DesiredState.Reset();
	_currentState = DesiredState;
}