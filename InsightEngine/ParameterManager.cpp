#include "pch.h"
#include "ParameterManager.h"

using namespace insight;

#pragma region RenderParameter
RenderParameter::RenderParameter()
{
	for (int i = 0; i < NUM_THREADS + 1; i++) {
		m_auiValueID[i] = 0;
	}
}
//--------------------------------------------------------------------------------
RenderParameter::RenderParameter(RenderParameter& copy)
{
	m_sParameterName = copy.m_sParameterName;
}
//--------------------------------------------------------------------------------
RenderParameter::~RenderParameter()
{
}
//--------------------------------------------------------------------------------
std::wstring& RenderParameter::GetName()
{
	return(m_sParameterName);
}
//--------------------------------------------------------------------------------
void RenderParameter::SetName(const std::wstring& name)
{
	m_sParameterName = name;
}
//--------------------------------------------------------------------------------
void RenderParameter::InitializeParameterData(void* pData)
{
	for (int i = 0; i <= NUM_THREADS; i++)
		SetParameterData(pData, i);
}
//--------------------------------------------------------------------------------
//void RenderParameter::UnInitializeParameterData( void* pData )
//{
//	for ( int i = 0; i <= NUM_THREADS; i++ )
//		ResetParameterData( pData, i );
//}
//--------------------------------------------------------------------------------
unsigned int RenderParameter::GetValueID(unsigned int threadID)
{
	assert(threadID >= 0);
	assert(threadID < NUM_THREADS + 1);

	return(m_auiValueID[threadID]);
}
//--------------------------------------------------------------------------------
//RenderParameter* RenderParameter::CreateCopy()
//{
//	RenderParameter* pParam = 0;
//
//	switch ( this->GetParameterType() )
//	{
//	case VECTOR:
//		pParam = new VectorParameterDX11();
//		pParam->SetName( GetName() );
//		pParam->UpdateValue( this );
//		break;
//	case MATRIX:
//		pParam = new MatrixParameterDX11();
//		pParam->SetName( GetName() );
//		pParam->UpdateValue( this );
//		break;
//	case MATRIX_ARRAY:
//		pParam = new MatrixArrayParameterDX11( ((MatrixArrayParameterDX11*)this)->GetMatrixCount() );
//		pParam->SetName( GetName() );
//		pParam->UpdateValue( this );
//		break;
//	case SHADER_RESOURCE:
//		pParam = new ShaderResourceParameterDX11();
//		pParam->SetName( GetName() );
//		pParam->UpdateValue( this );
//		break;
//	case UNORDERED_ACCESS:
//		pParam = new UnorderedAccessParameterDX11();
//		pParam->SetName( GetName() );
//		pParam->UpdateValue( this );
//		break;
//	case CBUFFER:
//		pParam = new ConstantBufferParameterDX11();
//		pParam->SetName( GetName() );
//		pParam->UpdateValue( this );
//		break;
//	case SAMPLER:
//		pParam = new SamplerParameterDX11();
//		pParam->SetName( GetName() );
//		pParam->UpdateValue( this );
//		break;
//	}
//
//	return( pParam );
//}
//--------------------------------------------------------------------------------

#pragma endregion


#pragma region ConstantBufferParameter
ConstantBufferParameter::ConstantBufferParameter()
{
	for (int i = 0; i <= NUM_THREADS; i++)
		m_iCBuffer[i] = -1;
}
//--------------------------------------------------------------------------------
ConstantBufferParameter::ConstantBufferParameter(ConstantBufferParameter& copy)
{
	for (int i = 0; i <= NUM_THREADS; i++)
		m_iCBuffer[i] = copy.m_iCBuffer[i];
}
//--------------------------------------------------------------------------------
ConstantBufferParameter::~ConstantBufferParameter()
{
}
//--------------------------------------------------------------------------------
void ConstantBufferParameter::SetParameterData(void* pData, unsigned int threadID)
{
	assert(threadID >= 0);
	assert(threadID < NUM_THREADS + 1);

	m_iCBuffer[threadID] = *reinterpret_cast<int*>(pData);
}
//--------------------------------------------------------------------------------
//void ConstantBufferParameter::ResetParameterData( void* pData, unsigned int threadID )
//{
//	assert( threadID >= 0 );
//	assert( threadID < NUM_THREADS+1 );
//
//	if ( m_iCBuffer[threadID] == *reinterpret_cast<int*>( pData ) ) {
//		m_iCBuffer[threadID] = -1;
//	}
//}
//--------------------------------------------------------------------------------
const ParameterType ConstantBufferParameter::GetParameterType()
{
	return(CBUFFER);
}
//--------------------------------------------------------------------------------
int ConstantBufferParameter::GetIndex(unsigned int threadID)
{
	assert(threadID >= 0);
	assert(threadID < NUM_THREADS + 1);

	return(m_iCBuffer[threadID]);
}
//--------------------------------------------------------------------------------
//void ConstantBufferParameter::UpdateValue( RenderParameter* pParameter, unsigned int threadID )
//{
//	assert( threadID >= 0 );
//	assert( threadID < NUM_THREADS+1 );
//
//	if ( pParameter )
//	{
//		if ( ( pParameter->GetParameterType() == CBUFFER ) && ( pParameter->GetName() == this->GetName() ) )
//		{
//			ConstantBufferParameter* pBuffer = (ConstantBufferParameter*)pParameter;
//			m_iCBuffer[threadID] = pBuffer->GetIndex( threadID );
//		}
//	}
//}
#pragma endregion
