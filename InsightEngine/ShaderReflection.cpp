#include "pch.h"
#include "ShaderReflection.h"

#include "Shader.h"
#include "RenderingPipeline.h"

#include "Renderer.h"
#include "ParameterManager.h"
#include "RenderParameter.h"
#include "PipeBufferDesc.h"

#include "PipeBuffer.h"

using namespace insight;

#pragma region ShaderReflection
ShaderReflection::ShaderReflection() {}
ShaderReflection::~ShaderReflection() {}

void ShaderReflection::InitializeConstantBuffers(IParameterManager* pParameterManager) {
	for (size_t i = 0; i < ConstantBuffers.size(); ++i) {
		if (ConstantBuffers[i].Description.Type == D3D11_CT_CBUFFER) {
			int index = pParameterManager->GetConstantBufferParameter(ConstantBuffers[i].pParamRef);

			if (index == -1) {
				for (int thread = 0; thread <= NUM_THREADS; ++thread) {
					PipeBufferDesc cbufferDesc;
					cbufferDesc.SetAsConstantBuffer(ConstantBuffers[i].Description.Size, true);

					std::shared_ptr<PipeResourceProxy> pResource = Renderer::Get()->CreateConstantBuffer(&cbufferDesc, nullptr);
					index = pResource->_iResource;

					ConstantBuffers[i].pParamRef->SetParameterData(&index, thread);

					for (size_t j = 0; j < ConstantBuffers[i].Variables.size(); ++j) {
						ConstantBufferMapping mapping;

						mapping.pParameter = ConstantBuffers[i].Parameters[j];
						mapping.offset = ConstantBuffers[i].Variables[j].StartOffset;
						mapping.size = ConstantBuffers[i].Variables[j].Size;
						mapping.elements = ConstantBuffers[i].Types[j].Elements;
						mapping.varclass = ConstantBuffers[i].Types[j].Class;
						mapping.valueID = -1;

						ConstantBuffer* pConstantBuffer = Renderer::Get()->GetConstantBufferByIndex(pResource->_iResource);
						pConstantBuffer->AddMapping(mapping);
					}
				}
			}
			else {
				ConstantBuffer* pConstantBuffer = Renderer::Get()->GetConstantBufferByIndex(index);

				if (pConstantBuffer->GetAutoUpdate()) {
					for (size_t j = 0; j < ConstantBuffers[i].Variables.size(); ++j) {
						ConstantBufferMapping mapping;

						mapping.pParameter = ConstantBuffers[i].Parameters[j];
						mapping.offset = ConstantBuffers[i].Variables[j].StartOffset;
						mapping.size = ConstantBuffers[i].Variables[j].Size;
						mapping.elements = ConstantBuffers[i].Types[j].Elements;
						mapping.varclass = ConstantBuffers[i].Types[j].Class;
						mapping.valueID = -1;

						if (!pConstantBuffer->ContainsMapping(i, mapping)) {
							// ...
						}
					}
				}
			}
		}
	}
}
void ShaderReflection::UpdateParameters(RenderingPipeline* pImmPipeline, IParameterManager* pParameterManager) {}
void ShaderReflection::BindParameters(ShaderType type, RenderingPipeline* pImmPipeline, IParameterManager* pParameterManager) {
	for (unsigned int i = 0; i < ResourceBindings.size(); ++i) {
		unsigned int slot = ResourceBindings[i].BindPoint;

		switch (ResourceBindings[i].Type)
		{
		case D3D_SIT_CBUFFER:
		case D3D_SIT_TBUFFER:
			pImmPipeline->BindConstantBufferParameter(type, ResourceBindings[i].pParamRef, slot, pParameterManager);
			break;
		default:
			break;
		}
	}
}

void ShaderReflection::PrintShaderDetails() {

}

void ShaderReflection::SetName(const std::wstring& name) {
	Name = name;
}
std::wstring ShaderReflection::GetName() {
	return Name;
}
#pragma endregion


#pragma region ShaderReflectionFactory
ShaderReflection* ShaderReflectionFactory::GenerateReflection(Shader& shader) {
	IParameterManager* pParameterManager = Renderer::Get()->GetParameterManager();

	ShaderReflection* pReflection = new ShaderReflection();

	ComPtr<ID3D11ShaderReflection> pReflector;
	HRESULT hr = D3DReflect(shader.GetCompiledShader()->GetBufferPointer(), shader.GetCompiledShader()->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(pReflector.GetAddressOf()));

	if (FAILED(hr)) {
		return nullptr;
	}

	D3D11_SHADER_DESC shaderDesc;
	pReflector->GetDesc(&shaderDesc);
	pReflection->ShaderDescription = shaderDesc;

	for (size_t i = 0; i < shaderDesc.InputParameters; ++i) {
		D3D11_SIGNATURE_PARAMETER_DESC inputDesc;
		pReflector->GetInputParameterDesc(i, &inputDesc);

		pReflection->InputSignatureParameters.push_back(inputDesc);
	}

	for (size_t i = 0; i < shaderDesc.OutputParameters; ++i) {
		D3D11_SIGNATURE_PARAMETER_DESC outputDesc;
		pReflector->GetOutputParameterDesc(i, &outputDesc);
		
		pReflection->OutputSignatureParameters.push_back(outputDesc);
	}

	for (size_t i = 0; i < shaderDesc.ConstantBuffers; ++i) {
		ID3D11ShaderReflectionConstantBuffer* pConstantBuffer = pReflector->GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC bufferDesc;
		pConstantBuffer->GetDesc(&bufferDesc);

		if (bufferDesc.Type == D3D_CT_CBUFFER || bufferDesc.Type == D3D_CT_TBUFFER) {
			ConstantBufferLayout bufferLayout;
			bufferLayout.Description = bufferDesc;
			bufferLayout.pParamRef = pParameterManager->GetConstantBufferParameterRef(ToUnicode(std::string(bufferLayout.Description.Name)));
			
			for (size_t j = 0; j < bufferLayout.Description.Variables; ++j) {
				ID3D11ShaderReflectionVariable* pVariable = pConstantBuffer->GetVariableByIndex(j);
				D3D11_SHADER_VARIABLE_DESC variableDesc;
				pVariable->GetDesc(&variableDesc);

				bufferLayout.Variables.push_back(variableDesc);

				ID3D11ShaderReflectionType* pType = pVariable->GetType();
				D3D11_SHADER_TYPE_DESC typeDesc;
				pType->GetDesc(&typeDesc);

				bufferLayout.Types.push_back(typeDesc);
				
				RenderParameter* pParameter = nullptr;
				if (typeDesc.Class == D3D_SVC_VECTOR) {
					// pParameter = pParameterManager->GetVectorParameterRef(ToUnicode(std::string(variableDesc.Name)));
				}
				else if ((typeDesc.Class == D3D_SVC_MATRIX_ROWS) || (typeDesc.Class == D3D_SVC_MATRIX_COLUMNS)) {
					unsigned int count = typeDesc.Elements;
					if (count == 0) {
						pParameter = pParameterManager->GetMatrixParameterRef(ToUnicode(std::string(variableDesc.Name)));
					}
					else {
						// pParameter = pParameterManager->GetMatrixArrayParameterRef(ToUnicode(std::string(variableDesc.Name)));
					}
				}

				bufferLayout.Parameters.push_back(pParameter);
			}

			pReflection->ConstantBuffers.push_back(bufferLayout);
		}
	}


	for (size_t i = 0; i < shaderDesc.BoundResources; ++i) {
		D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
		pReflector->GetResourceBindingDesc(i, &resourceDesc);

		ShaderInputBindDesc bindDesc(resourceDesc);
		
		if (resourceDesc.Type == D3D_SIT_CBUFFER || resourceDesc.Type == D3D_SIT_TBUFFER) {
			bindDesc.pParamRef = pParameterManager->GetConstantBufferParameterRef(bindDesc.Name);
		}
		else {
			/// ...
		}

		pReflection->ResourceBindings.push_back(bindDesc);
	}

	return pReflection;
}
#pragma endregion
