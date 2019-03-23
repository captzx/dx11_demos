#include "pch.h"
#include "ParameterManager.h"

#include "PipeResourceProxy.h"
#include "RenderParameter.h"

using namespace insight;

std::map<std::wstring, RenderParameter*> ParameterManager::sParameters;

ParameterManager::ParameterManager(unsigned int id) {
	_uiID = id;
	_pManagerParent = nullptr;

	_pWorldMatrix = GetMatrixParameterRef(std::wstring(L"WorldMatrix"));
	_pViewMatrix = GetMatrixParameterRef(std::wstring(L"ViewMatrix"));
	_pProjMatrix = GetMatrixParameterRef(std::wstring(L"ProjMatrix"));
}
ParameterManager::~ParameterManager() {
	std::map< std::wstring, RenderParameter* >::iterator iter = sParameters.begin();
	while (iter != sParameters.end()){
		SAFE_DELETE(iter->second);
		++iter;
	}

	sParameters.clear();
}

unsigned int ParameterManager::GetID(){
	return _uiID;
}
void ParameterManager::SetMatrixParameter(RenderParameter* pParameter, XMFLOAT4X4* pMatrix){
	if (pParameter->GetParameterType() == MATRIX)
		pParameter->SetParameterData(reinterpret_cast<void*>(pMatrix), GetID());
	else {
		// name collision;
	}
}
void ParameterManager::SetMatrixParameter(const std::wstring& name, XMFLOAT4X4* pMatrix) {
	RenderParameter* pParameter = GetRenderParameterRef(name);

	if (!pParameter) {
		pParameter = new MatrixParameter();
		pParameter->SetName(name);

		sParameters[name] = pParameter;

		pParameter->InitializeParameterData(reinterpret_cast<void*>(pParameter));
	}
	else {
		if (pParameter->GetParameterType() == MATRIX) {
			pParameter->SetParameterData(reinterpret_cast<void*>(pParameter), GetID());
		}
		// else name collision
	}
}

void ParameterManager::SetConstantBufferParameter(const std::wstring& name, std::shared_ptr<PipeResourceProxy> resource) {
	RenderParameter* pParameter = sParameters[name];

	if (!pParameter) {
		pParameter = new ConstantBufferParameter();
		pParameter->SetName(name);
		sParameters[name] = reinterpret_cast<RenderParameter*>(pParameter);

		pParameter->InitializeParameterData(reinterpret_cast<void*>(resource->_iResource));
	}
	else {
		if (pParameter->GetParameterType() == CBUFFER)
			pParameter->SetParameterData(reinterpret_cast<void*>(resource->_iResource), GetID());
		// else // name	collision
	}
}
void ParameterManager::SetConstantBufferParameter(RenderParameter* pParameter, std::shared_ptr<PipeResourceProxy> resource) {
	if (pParameter->GetParameterType() == CBUFFER) {
		pParameter->SetParameterData(reinterpret_cast<void*>(resource->_iResource), GetID());
	}
	// else name collision
}

RenderParameter* ParameterManager::GetRenderParameterRef(const std::wstring& name) {
	RenderParameter* pParameter = sParameters[name];

	if (!pParameter && _pManagerParent) {
		pParameter = _pManagerParent->GetRenderParameterRef(name);
	}

	return pParameter;
}
MatrixParameter* ParameterManager::GetMatrixParameterRef(const std::wstring name) {
	RenderParameter* pParameter = GetRenderParameterRef(name);

	if (!pParameter) {
		pParameter = new MatrixParameter();
		pParameter->SetName(name);

		sParameters[name] = pParameter;
	}

	return reinterpret_cast<MatrixParameter*>(pParameter);
}
ConstantBufferParameter* ParameterManager::GetConstantBufferParameterRef(const std::wstring name) {
	RenderParameter* pParameter = GetRenderParameterRef(name);

	if (!pParameter) {
		pParameter = new ConstantBufferParameter();
		pParameter->SetName(name);

		sParameters[name] = pParameter;
	}

	return reinterpret_cast<ConstantBufferParameter*>(pParameter);
}


XMMATRIX ParameterManager::GetMatrixParameter(RenderParameter* pParameter) {
	XMMATRIX result = XMMatrixIdentity();

	if (pParameter->GetParameterType() == MATRIX) {
		result = reinterpret_cast<MatrixParameter*>(pParameter)->GetMatrix(GetID());
	}

	return result;
}

int ParameterManager::GetConstantBufferParameter(RenderParameter* pParameter) {
	int result = -1;

	if (pParameter->GetParameterType() == CBUFFER) {
		result = reinterpret_cast<ConstantBufferParameter*>(pParameter)->GetResourceIndex(GetID());
	}

	return result;
}

XMMATRIX ParameterManager::GetMatrixParameter(const std::wstring name) {
	XMMATRIX result = XMMatrixIdentity();

	RenderParameter* pParameter = GetRenderParameterRef(name);

	if (!pParameter) {
		if (pParameter->GetParameterType() == MATRIX) {
			result = reinterpret_cast<MatrixParameter*>(pParameter)->GetMatrix(GetID());
		}
	}
	else {
		pParameter = new MatrixParameter();
		pParameter->SetName(name);

		sParameters[name] = pParameter;
	}

	return result;
}

int ParameterManager::GetConstantBufferParameter(const std::wstring name) {
	int result = -1;

	RenderParameter* pParameter = GetRenderParameterRef(name);

	if (pParameter) {
		if (pParameter->GetParameterType() == CBUFFER) {
			result = reinterpret_cast<ConstantBufferParameter*>(pParameter)->GetResourceIndex(GetID());
		}
	}
	else {
		pParameter = new ConstantBufferParameter();
		pParameter->SetName(name);
		sParameters[name] = pParameter;
	}

	return result;
}

void ParameterManager::SetWorldMatrixParameter(XMFLOAT4X4* pMatrix) {
	SetMatrixParameter(_pWorldMatrix, pMatrix);
}
void ParameterManager::SetViewMatrixParameter(XMFLOAT4X4* pMatrix) {
	SetMatrixParameter(_pViewMatrix, pMatrix);
}
void ParameterManager::SetProjMatrixParameter(XMFLOAT4X4* pMatrix) {
	SetMatrixParameter(_pProjMatrix, pMatrix);
}