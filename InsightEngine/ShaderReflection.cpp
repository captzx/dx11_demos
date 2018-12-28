#include "pch.h"
#include "ShaderReflection.h"

#include "Shader.h"
#include "Renderer.h"

#include "ParameterManager.h"
#include "PipeBufferDesc.h"
#include "PipeBuffer.h"

#include "D3DEnumConversion.h"
#include "RenderingPipeline.h"

using namespace insight;

#pragma endregion ShaderReflection
ShaderReflection::ShaderReflection() {

}
ShaderReflection::~ShaderReflection() {

}

void ShaderReflection::InitializeConstantBuffers(IParameterManager* pParamManager) {
	for (unsigned int i = 0; i < ConstantBuffers.size(); i++)
	{
		if (ConstantBuffers[i].Description.Type == D3D11_CT_CBUFFER)
		{
			// Get the index of the constant buffer parameter currently set with 
			// this name.

			int index = pParamManager->GetConstantBufferParameter(ConstantBuffers[i].pParamRef);

			// If the constant buffer does not exist yet, create a one with 
			// standard options - writeable by the CPU and only bound as a 
			// constant buffer.  By automatically creating the constant buffer
			// we reduce the amount of code to do common tasks, but still allow
			// the user to create and use a special buffer if they want.

			if (index == -1)
			{
				// Here we create one constant buffer for each thread that could potentially
				// be rendering, and then set each one accordingly within the parameter 
				// reference that we have for this buffer.

				for (int thread = 0; thread < NUM_THREADS + 1; thread++)
				{
					// Configure the buffer for the needed size and dynamic updating.
					PipeBufferDesc cbuffer;
					cbuffer.SetAsConstantBuffer(ConstantBuffers[i].Description.Size, true);

					// Create the buffer and set it as a constant buffer parameter.  This
					// creates a parameter object to be used in the future.
					ResourcePtr resource = Renderer::Get()->CreateConstantBuffer(&cbuffer, 0);
					index = resource->_iResource;

					//ConstantBuffers[i].pParamRef->InitializeParameterData( &index );
					ConstantBuffers[i].pParamRef->SetParameterData(&index, thread);

					// Now we load the variable information into each of the constant
					// buffers.  This allows the buffer to know how to update itself
					// with the parameter system.

					for (unsigned int j = 0; j < ConstantBuffers[i].Variables.size(); j++)
					{
						ConstantBufferMapping mapping;

						mapping.pParameter = ConstantBuffers[i].Parameters[j];
						mapping.offset = ConstantBuffers[i].Variables[j].StartOffset;
						mapping.size = ConstantBuffers[i].Variables[j].Size;
						mapping.elements = ConstantBuffers[i].Types[j].Elements;
						mapping.varclass = ConstantBuffers[i].Types[j].Class;
						mapping.valueID = -1;

						ConstantBuffer* constBuffer = Renderer::Get()->GetConstantBufferByIndex(resource->_iResource);
						constBuffer->AddMapping(mapping);
					}
				}
			}
			else {

				// If we get here, that means we are trying to initialize a constant buffer
				// that has already been set as a parameter before.  We need to compare if this
				// constant buffer has the same variables in it as the reflection data that we
				// are currently working with.  This can be done by getting the buffer, then
				// examining its mapping data and comparing that with the current reflection
				// provided mapping data.
				//
				// It is sufficient to check only one of the parameter's constant buffers, since
				// all of the buffers for multiple threads should be identical (as created above).

				ConstantBuffer* pConstBuffer = Renderer::Get()->GetConstantBufferByIndex(index);

				if (pConstBuffer->GetAutoUpdate()) {

					// Only check this buffer if we are auto-updating.  If not, then we are 
					// expecting something else to manage the contents of this buffer, and there
					// is no need for the mapping information.

					for (unsigned int j = 0; j < ConstantBuffers[i].Variables.size(); j++)
					{
						ConstantBufferMapping mapping;

						mapping.pParameter = ConstantBuffers[i].Parameters[j];
						mapping.offset = ConstantBuffers[i].Variables[j].StartOffset;
						mapping.size = ConstantBuffers[i].Variables[j].Size;
						mapping.elements = ConstantBuffers[i].Types[j].Elements;
						mapping.varclass = ConstantBuffers[i].Types[j].Class;
						mapping.valueID = -1;

						if (!pConstBuffer->ContainsMapping(j, mapping)) {

							std::wstringstream message;
							message << L"Constant buffer by this name is already mapped, but with a different mapping!" << std::endl;
							message << L"See constant buffer: " << ConstantBuffers[i].pParamRef->GetName() << std::endl;
							message << L" - parameter: " << mapping.pParameter->GetName() << std::endl;
							message << L" - offset: " << mapping.offset << std::endl;
							message << L" - size: " << mapping.size << std::endl;
							message << L" - elements: " << mapping.elements << std::endl;
							message << L" - class: " << TO_STRING_D3D_SHADER_VARIABLE_CLASS(mapping.varclass) << std::endl << std::endl;

							//Log::Get().Write(message.str());
							//EventManager::Get()->ProcessEvent(EvtErrorMessagePtr(new EvtErrorMessage(message.str())));

						}
					}
				}
			}
		}
	}
}
void ShaderReflection::UpdateParameters(RenderingPipeline* pPipeline, IParameterManager* pParamManager) {
	// Renderer will call this function when binding the shader to the pipeline.
	// This function will then call renderer functions to update each constant
	// buffer needed for the shader.

	for (unsigned int i = 0; i < ConstantBuffers.size(); i++)
	{
		if (ConstantBuffers[i].Description.Type == D3D11_CT_CBUFFER)
		{
			// Get the index of the constant buffer parameter currently set with 
			// this name.

			int index = pParamManager->GetConstantBufferParameter(ConstantBuffers[i].pParamRef);

			// If the constant buffer does not exist yet, create a one with 
			// standard options - writeable by the CPU and only bound as a 
			// constant buffer.  By automatically creating the constant buffer
			// we reduce the amount of code to do common tasks, but still allow
			// the user to create and use a special buffer if they want.

			if (index == -1)
			{
				// This section of the code should never be reached anymore - all CBs should
				// be initially created when a shader is compiled if it doesn't already exist.
				// If we do end up here, send a message about it!
				//Log::Get().Write(L"Uh oh - creating a constant buffer in the Shader::UpdateParameters functions!!!!");

				// Configure the buffer for the needed size and dynamic updating.
				PipeBufferDesc cbuffer;
				cbuffer.SetAsConstantBuffer(ConstantBuffers[i].Description.Size, true);

				// Create the buffer and set it as a constant buffer parameter.  This
				// creates a parameter object to be used in the future.
				ResourcePtr resource = Renderer::Get()->CreateConstantBuffer(&cbuffer, 0);
				index = resource->_iResource;

				pParamManager->SetConstantBufferParameter(ConstantBuffers[i].pParamRef, resource);
			}


			// Check if the resource is a constant buffer before accessing it!

			ConstantBuffer* pBuffer = Renderer::Get()->GetConstantBufferByIndex(index);

			// Test the index to ensure that it is a constant buffer.  If the method above returns
			// a non-null result, then this is a constant buffer.

			if (pBuffer) {

				// Here all of the individual variables from the reflection data are used to
				// update the data held by the constant buffer.

				if (pBuffer->GetAutoUpdate()) {
					pBuffer->EvaluateMappings(pPipeline, pParamManager);
				}

			}
			else {
				//Log::Get().Write(L"Trying to update a constant buffer that isn't a constant buffer!");
			}
		}
	}
}
void ShaderReflection::BindParameters(ShaderType type, RenderingPipeline* pPipeline, IParameterManager* pParamManager) {
	// Here the shader will attempt to bind each parameter needed by the pipeline.
	// The renderer supplies methods for binding a parameter based on the name
	// and type of parameter, in addition to the pipeline stage to bind the 
	// parameter to.

	for (unsigned int i = 0; i < ResourceBindings.size(); i++)
	{
		UINT slot = ResourceBindings[i].BindPoint;

		switch (ResourceBindings[i].Type)
		{
		case D3D_SIT_CBUFFER:
		case D3D_SIT_TBUFFER:
			pPipeline->BindConstantBufferParameter(type, ResourceBindings[i].pParamRef, slot, pParamManager);
			break;
		/*case D3D_SIT_SAMPLER:
			pPipeline->BindSamplerStateParameter(type, ResourceBindings[i].pParamRef, slot, pParamManager);
			break;
		case D3D_SIT_TEXTURE:
		case D3D_SIT_STRUCTURED:
		case D3D_SIT_BYTEADDRESS:
			pPipeline->BindShaderResourceParameter(type, ResourceBindings[i].pParamRef, slot, pParamManager);
			break;
		case D3D_SIT_UAV_RWSTRUCTURED:
		case D3D_SIT_UAV_RWTYPED:
		case D3D_SIT_UAV_RWBYTEADDRESS:
		case D3D_SIT_UAV_APPEND_STRUCTURED:
		case D3D_SIT_UAV_CONSUME_STRUCTURED:
		case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
			pPipeline->BindUnorderedAccessParameter(type, ResourceBindings[i].pParamRef, slot, pParamManager);
			break;*/
		}
	}
}

void ShaderReflection::PrintShaderDetails() {
	std::wstringstream s;

	s << L"----------------------------------------------------------------------" << std::endl;
	s << L"Shader details printout for: " << Name << std::endl;
	s << L"----------------------------------------------------------------------" << std::endl;

	s << L"Shader Description: " << std::endl;
	s << TO_STRING_D3D11_SHADER_DESC(this->ShaderDescription);

	s << std::endl;

	s << L"Number of Input Signature Elements: " << InputSignatureParameters.size() << std::endl;
	for (unsigned int i = 0; i < InputSignatureParameters.size(); i++)
	{
		s << L"  Semantic Name: " << InputSignatureParameters[i].SemanticName;
		s << L", Semantic Index: " << InputSignatureParameters[i].SemanticIndex;
		s << L", Register: " << InputSignatureParameters[i].Register;
		s << L", System Value Type: " << TO_STRING_D3D_NAME(InputSignatureParameters[i].SystemValueType);
		s << L", Component Type: " << TO_STRING_D3D_REGISTER_COMPONENT_TYPE(InputSignatureParameters[i].ComponentType);
		s << L", Mask: " << (unsigned int)InputSignatureParameters[i].Mask;
		s << L", Read/Write Mask: " << (unsigned int)InputSignatureParameters[i].ReadWriteMask;
		s << std::endl;
	}
	s << std::endl;

	s << L"Number of Output Signature Elements: " << OutputSignatureParameters.size() << std::endl;
	for (unsigned int i = 0; i < OutputSignatureParameters.size(); i++)
	{
		s << L"  Semantic Name: " << OutputSignatureParameters[i].SemanticName;
		s << L", Semantic Index: " << OutputSignatureParameters[i].SemanticIndex;
		s << L", Register: " << OutputSignatureParameters[i].Register;
		s << L", System Value Type: " << TO_STRING_D3D_NAME(OutputSignatureParameters[i].SystemValueType);
		s << L", Component Type: " << TO_STRING_D3D_REGISTER_COMPONENT_TYPE(OutputSignatureParameters[i].ComponentType);
		s << L", Mask: " << (unsigned int)OutputSignatureParameters[i].Mask;
		s << L", Read/Write Mask: " << (unsigned int)OutputSignatureParameters[i].ReadWriteMask;
		s << std::endl;
	}
	s << std::endl;

	s << L"Number of Constant Buffer Descriptions: " << ConstantBuffers.size() << std::endl;
	for (unsigned int i = 0; i < ConstantBuffers.size(); i++)
	{
		s << L"  Buffer Name: " << ConstantBuffers[i].Description.Name;
		s << L", Buffer Type: " << TO_STRING_D3D_CBUFFER_TYPE(ConstantBuffers[i].Description.Type);
		s << L", Variables: " << ConstantBuffers[i].Description.Variables;
		s << L", Size: " << ConstantBuffers[i].Description.Size;
		s << L", Flags: " << ConstantBuffers[i].Description.uFlags;

		for (unsigned int j = 0; j < ConstantBuffers[i].Variables.size(); j++)
		{
			s << std::endl << L"    ";
			s << L"Variable Name: " << ConstantBuffers[i].Variables[j].Name;
			s << L", Start Offset: " << ConstantBuffers[i].Variables[j].StartOffset;
			s << L", Size: " << ConstantBuffers[i].Variables[j].Size;
			s << L", Flags: " << ConstantBuffers[i].Variables[j].uFlags;
			s << L", Start Texture: " << (int)ConstantBuffers[i].Variables[j].StartTexture;
			s << L", Texture Size: " << ConstantBuffers[i].Variables[j].TextureSize;
			s << L", Start Sampler: " << (int)ConstantBuffers[i].Variables[j].StartSampler;
			s << L", Sampler Size: " << ConstantBuffers[i].Variables[j].SamplerSize;
		}


		for (unsigned int j = 0; j < ConstantBuffers[i].Types.size(); j++)
		{
			s << std::endl << L"    ";
			s << L"Variable Type Name: " << ConstantBuffers[i].Types[j].Name;
			s << L", Class: " << TO_STRING_D3D_SHADER_VARIABLE_CLASS(ConstantBuffers[i].Types[j].Class);
			s << L", Type: " << TO_STRING_D3D_SHADER_VARIABLE_TYPE(ConstantBuffers[i].Types[j].Type);
			s << L", Rows: " << ConstantBuffers[i].Types[j].Rows;
			s << L", Columns: " << ConstantBuffers[i].Types[j].Columns;
			s << L", Elements: " << ConstantBuffers[i].Types[j].Elements;
			s << L", Members: " << ConstantBuffers[i].Types[j].Members;
			s << L", Offset: " << ConstantBuffers[i].Types[j].Offset;
		}

		s << std::endl;
	}
	s << std::endl;

	s << L"Number of Resource Binding Descriptions: " << ResourceBindings.size() << std::endl;
	for (unsigned int i = 0; i < ResourceBindings.size(); i++)
	{
		s << L"  Name: " << ResourceBindings[i].Name;
		s << L", Type: " << TO_STRING_D3D_SHADER_INPUT_TYPE(ResourceBindings[i].Type);
		s << L", Bind Point: " << ResourceBindings[i].BindPoint;
		s << L", Bind Count: " << ResourceBindings[i].BindCount;
		s << L", Flags: " << ResourceBindings[i].uFlags;
		s << L", Resource Return Type: " << TO_STRING_D3D_RESOURCE_RETURN_TYPE(ResourceBindings[i].ReturnType);
		s << L", Dimension: " << ResourceBindings[i].Dimension;
		s << L", Number of Samples: " << ResourceBindings[i].NumSamples;
		s << std::endl;
	}

	s << std::endl;

	//LPVOID pBlobBuffer = pCompiledShader->GetBufferPointer();
	//const char* pMessage = (const char*)pBlobBuffer;

	//s << pMessage << std::endl;

	s << L"----------------------------------------------------------------------" << std::endl;

	//Log::Get().Write(s.str());

}

void ShaderReflection::SetName(const std::wstring& name) {
	Name = name;
}
std::wstring ShaderReflection::GetName() {
	return(Name);
}
#pragma endregion ShaderReflection

#pragma region ShaderReflectionFactory
ShaderReflectionFactory::ShaderReflectionFactory(){
	
}

ShaderReflectionFactory::~ShaderReflectionFactory(){

}
ShaderReflection* ShaderReflectionFactory::GenerateReflection(Shader& shader){
	// TODO: Fix this hack - I'm getting the parameter manager reference from the
	//       renderer here, but it shouldn't be needed at all here.  The 
	//       references should be resolved in an outside class or container.

	IParameterManager* pParamMgr = Renderer::Get()->m_pParamMgr;

	// Create the reflection interface to query information about the shader.  Note that
	// this reflection interface does not depend on the shader type!

	ShaderReflection* pReflection = new ShaderReflection();

	ComPtr<ID3D11ShaderReflection> pReflector;
	HRESULT hr = D3DReflect(shader.GetCompiledShader()->GetBufferPointer(), shader.GetCompiledShader->GetBufferSize(),
		IID_ID3D11ShaderReflection, reinterpret_cast<void**>(pReflector.GetAddressOf()));

	if (FAILED(hr)){
		////Log::Get().Write(L"Failed to create shader reflection interface!");
		return(nullptr);
	}


	// Get the top level shader information, including the number of constant buffers,
	// as well as the number bound resources (constant buffers + other objects), the
	// number of input elements, and the number of output elements for the shader.

	D3D11_SHADER_DESC desc;
	pReflector->GetDesc(&desc);
	pReflection->ShaderDescription = desc;


	// Get the input and output signature description arrays.  These can be used later
	// for verification of linking shader stages together.
	for (UINT i = 0; i < desc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC input_desc;
		pReflector->GetInputParameterDesc(i, &input_desc);
		pReflection->InputSignatureParameters.push_back(input_desc);
	}
	for (UINT i = 0; i < desc.OutputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC output_desc;
		pReflector->GetOutputParameterDesc(i, &output_desc);
		pReflection->OutputSignatureParameters.push_back(output_desc);
	}


	// Get the constant buffer information, which will be used for setting parameters
	// for use by this shader at rendering time.

	for (UINT i = 0; i < desc.ConstantBuffers; i++)
	{
		ID3D11ShaderReflectionConstantBuffer* pConstBuffer = pReflector->GetConstantBufferByIndex(i);

		D3D11_SHADER_BUFFER_DESC bufferDesc;
		pConstBuffer->GetDesc(&bufferDesc);

		if (bufferDesc.Type == D3D_CT_CBUFFER || bufferDesc.Type == D3D_CT_TBUFFER)
		{
			ConstantBufferLayout BufferLayout;
			BufferLayout.Description = bufferDesc;
			BufferLayout.pParamRef = pParamMgr->GetConstantBufferParameterRef(
				ToUnicode(std::string(BufferLayout.Description.Name)));

			// Load the description of each variable for use later on when binding a buffer
			for (UINT j = 0; j < BufferLayout.Description.Variables; j++)
			{
				// Get the variable description and store it
				ID3D11ShaderReflectionVariable* pVariable = pConstBuffer->GetVariableByIndex(j);
				D3D11_SHADER_VARIABLE_DESC var_desc;
				pVariable->GetDesc(&var_desc);

				BufferLayout.Variables.push_back(var_desc);

				// Get the variable type description and store it
				ID3D11ShaderReflectionType* pType = pVariable->GetType();
				D3D11_SHADER_TYPE_DESC type_desc;
				pType->GetDesc(&type_desc);

				BufferLayout.Types.push_back(type_desc);

				// Get references to the parameters for binding to these variables.
				RenderParameter* pParam = 0;
				if (type_desc.Class == D3D_SVC_VECTOR)
				{
					pParam = pParamMgr->GetVectorParameterRef(ToUnicode(std::string(var_desc.Name)));
				}
				else if ((type_desc.Class == D3D_SVC_MATRIX_ROWS) ||
					(type_desc.Class == D3D_SVC_MATRIX_COLUMNS))
				{
					// Check if it is an array of matrices first...
					unsigned int count = type_desc.Elements;
					if (count == 0)
					{
						pParam = pParamMgr->GetMatrixParameterRef(ToUnicode(std::string(var_desc.Name)));
					}
					else
					{
						pParam = pParamMgr->GetMatrixArrayParameterRef(ToUnicode(std::string(var_desc.Name)), count);
					}
				}

				BufferLayout.Parameters.push_back(pParam);
			}

			pReflection->ConstantBuffers.push_back(BufferLayout);
		}
	}


	// Get the overall resource binding information for this shader.  This includes
	// the constant buffers, plus all of the other objects that can be bound to the
	// pipeline with resource views (shader resource views and unordered access views).

	for (UINT i = 0; i < desc.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC resource_desc;
		pReflector->GetResourceBindingDesc(i, &resource_desc);
		ShaderInputBindDesc binddesc(resource_desc);

		if (resource_desc.Type == D3D_SIT_CBUFFER || resource_desc.Type == D3D_SIT_TBUFFER)
		{
			binddesc.pParamRef = pParamMgr->GetConstantBufferParameterRef(binddesc.Name);
		}
		/*else if (resource_desc.Type == D3D_SIT_TEXTURE || resource_desc.Type == D3D_SIT_STRUCTURED)
		{
			binddesc.pParamRef = pParamMgr->GetShaderResourceParameterRef(binddesc.Name);
		}
		else if (resource_desc.Type == D3D_SIT_SAMPLER)
		{
			binddesc.pParamRef = pParamMgr->GetSamplerStateParameterRef(binddesc.Name);
		}
		else if (resource_desc.Type == D3D_SIT_UAV_RWTYPED || resource_desc.Type == D3D_SIT_UAV_RWSTRUCTURED
			|| resource_desc.Type == D3D_SIT_BYTEADDRESS || resource_desc.Type == D3D_SIT_UAV_RWBYTEADDRESS
			|| resource_desc.Type == D3D_SIT_UAV_APPEND_STRUCTURED || resource_desc.Type == D3D_SIT_UAV_CONSUME_STRUCTURED
			|| resource_desc.Type == D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER)
		{
			binddesc.pParamRef = pParamMgr->GetUnorderedAccessParameterRef(binddesc.Name);
		}
*/

		pReflection->ResourceBindings.push_back(binddesc);
	}

	return(pReflection);
}
#pragma endregion ShaderReflectionFactory
