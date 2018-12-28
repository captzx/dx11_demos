#pragma once

namespace insight {
	enum ParameterType{
		VECTOR,
		MATRIX,
		MATRIX_ARRAY,
		SHADER_RESOURCE,
		UNORDERED_ACCESS,
		CBUFFER,
		SAMPLER,
		ENTITY
	};
	class RenderParameter {
	public:
		RenderParameter();
		RenderParameter(RenderParameter& copy);
		virtual ~RenderParameter();

		void SetName(const std::wstring& name);
		std::wstring& GetName();

		// Each parameter type will implement this method for a simple way
		// to tell what kind of data it uses.  This is important for handling
		// the parameters in a generic way, but still being able to perform
		// type checking.

		virtual const ParameterType GetParameterType() = 0;

		// Initializing parameter data sets all copies of this resource with
		// the provided data.  Internally this calls the SetParameterData() 
		// method on each thread's data copy, which is specialized by each 
		// concrete subclass.  The uninitialize method will reset the parameter
		// to a default value if the parameter's data matches the passed in data.

		void InitializeParameterData(void* pData);
		//void UnInitializeParameterData( void* pData );

		// Setting parameter data does what it sounds like - it takes a pointer
		// to the data and sets it in the data copy indicated by its thread ID.
		// Reset will default the data if the current data matches the passed in
		// data.

		virtual void SetParameterData(void* pData, unsigned int threadID = 0) = 0;
		//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 ) = 0;

		// This update function is a convenience function to allow 
		// RenderParameterDX11 subclasses to be referred to by their parent class
		// and automatically update the parameter stored in the parameter
		// manager.

		//virtual void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 ) = 0;

		// The value ID is used to efficiently determine when a parameter's value
		// has been changed.  Each parameter type will increment the value ID
		// after it has been changed to indicate that it should be re-evaluated.
		// This is especially important for updating constant buffer contents
		// only when needed.

		unsigned int GetValueID(unsigned int threadID = 0);

	protected:
		std::wstring	m_sParameterName;
		unsigned int	m_auiValueID[NUM_THREADS + 1];
	};

	//class VectorParameter:public RenderParameter{
	//
	//};

	//class MatrixParameter :public RenderParameter {
	//
	//}

	class ConstantBufferParameter :public RenderParameter {
	public:
		ConstantBufferParameter();
		ConstantBufferParameter(ConstantBufferParameter& copy);
		virtual ~ConstantBufferParameter();

		virtual void SetParameterData(void* pData, unsigned int threadID = 0);
		//virtual void ResetParameterData( void* pData, unsigned int threadID = 0 );

		virtual const ParameterType GetParameterType();

		//virtual void UpdateValue( RenderParameterDX11* pParameter, unsigned int threadID = 0 );

		int GetIndex(unsigned int threadID);

	protected:
		int		m_iCBuffer[NUM_THREADS + 1];
	};

	class PipeResourceProxy;
	typedef std::shared_ptr<PipeResourceProxy> ResourcePtr;
	class IParameterManager {
	public:
		IParameterManager() {};
		virtual ~IParameterManager() {};

		virtual unsigned int GetID() = 0;

		// Here we allow rendering parameters to be registered and set by name.  These 
		// parameters are then available for setting their value and subsequent use 
		// during rendering.

		//virtual void SetParameter( RenderParameter* pParameter ) = 0;
		/*virtual void SetVectorParameter(const std::wstring& name, Vector4f* pVector) = 0;
		virtual void SetMatrixParameter(const std::wstring& name, Matrix4f* pMatrix) = 0;
		virtual void SetSamplerParameter(const std::wstring& name, int* pID) = 0;
		virtual void SetShaderResourceParameter(const std::wstring& name, ResourcePtr resource) = 0;
		virtual void SetUnorderedAccessParameter(const std::wstring& name, ResourcePtr resource, unsigned int initial = -1) = 0;*/
		virtual void SetConstantBufferParameter(const std::wstring& name, ResourcePtr resource) = 0;
		/*virtual void SetMatrixArrayParameter(const std::wstring& name, int count, Matrix4f* pMatrices) = 0;*/

		/*virtual void SetVectorParameter(RenderParameter* pParameter, Vector4f* pVector) = 0;
		virtual void SetMatrixParameter(RenderParameter* pParameter, Matrix4f* pMatrix) = 0;
		virtual void SetSamplerParameter(RenderParameter* pParameter, int* pID) = 0;
		virtual void SetShaderResourceParameter(RenderParameter* pParameter, ResourcePtr resource) = 0;
		virtual void SetUnorderedAccessParameter(RenderParameter* pParameter, ResourcePtr resource, unsigned int initial = -1) = 0;*/
		virtual void SetConstantBufferParameter(RenderParameter* pParameter, ResourcePtr resource) = 0;
		/*virtual void SetMatrixArrayParameter(RenderParameter* pParameter, int count, Matrix4f* pMatrices) = 0;*/

		/*virtual RenderParameter* GetParameterRef(const std::wstring& name) = 0;
		virtual VectorParameter* GetVectorParameterRef(const std::wstring& name) = 0;
		virtual MatrixParameter* GetMatrixParameterRef(const std::wstring& name) = 0;
		virtual ShaderResourceParameter* GetShaderResourceParameterRef(const std::wstring& name) = 0;
		virtual UnorderedAccessParameter* GetUnorderedAccessParameterRef(const std::wstring& name) = 0;*/
		virtual ConstantBufferParameter* GetConstantBufferParameterRef(const std::wstring& name) = 0;
		/*virtual SamplerParameter* GetSamplerStateParameterRef(const std::wstring& name) = 0;
		virtual MatrixArrayParameter* GetMatrixArrayParameterRef(const std::wstring& name, int count) = 0;*/

		// Each of the parameter types can also be accessed to inspect their current
		// value prior to setting them.

		/*virtual Vector4f GetVectorParameter(RenderParameter* pParameter) = 0;
		virtual Matrix4f GetMatrixParameter(RenderParameter* pParameter) = 0;
		virtual int GetShaderResourceParameter(RenderParameter* pParameter) = 0;
		virtual int GetUnorderedAccessParameter(RenderParameter* pParameter) = 0;*/
		virtual int GetConstantBufferParameter(RenderParameter* pParameter) = 0;
		/*virtual int GetSamplerStateParameter(RenderParameter* pParameter) = 0;
		virtual Matrix4f* GetMatrixArrayParameter(RenderParameter* pParameter) = 0;*/

		/*virtual Vector4f GetVectorParameter(const std::wstring& name) = 0;
		virtual Matrix4f GetMatrixParameter(const std::wstring& name) = 0;
		virtual int GetShaderResourceParameter(const std::wstring& name) = 0;
		virtual int GetUnorderedAccessParameter(const std::wstring& name) = 0;*/
		virtual int GetConstantBufferParameter(const std::wstring& name) = 0;
		/*virtual int GetSamplerStateParameter(const std::wstring& name) = 0;
		virtual Matrix4f* GetMatrixArrayParameter(const std::wstring& name, int count) = 0;*/

		// The following matrix parameters are set with specialized functions to allow
		// the renderer to calculate the concatenated matrices.

		virtual void SetWorldMatrixParameter(XMMATRIX* pMatrix) = 0;
		virtual void SetViewMatrixParameter(XMMATRIX* pMatrix) = 0;
		virtual void SetProjMatrixParameter(XMMATRIX* pMatrix) = 0;

		// Allow the connection of multiple parameter managers for subsets of the 
		// complete parameter space to be isolated from the other regions if needed.
		// This can be helpful in distributed processing as seen in multithreaded
		// rendering.

		virtual void AttachParent(IParameterManager* pParent) = 0;
		virtual void DetachParent() = 0;
	};
}