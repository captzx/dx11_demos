#pragma once


namespace insight {
	enum ParameterType {
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
		virtual ~RenderParameter();

		void SetName(const std::wstring& name);
		std::wstring& GetName();

		void InitializeParameterData(void* pData);

		unsigned int GetValueID(unsigned int threadID = 0);

		virtual const ParameterType GetParameterType() = 0;
		virtual void SetParameterData(void* pData, unsigned int theradID = 0) = 0;

	protected:
		std::wstring _wsName;
		unsigned int _uiValueIDs[NUM_THREADS + 1];
	};


	class MatrixParameter :public RenderParameter {
	public:
		MatrixParameter();
		virtual ~MatrixParameter();

	public:
		virtual const ParameterType GetParameterType() override;
		virtual void SetParameterData(void* pData, unsigned int theradID = 0) override;
		
		XMMATRIX GetMatrix(unsigned int threadID);

	protected:
		XMFLOAT4X4 _Matrixs[NUM_THREADS + 1];
	};

	class ConstantBufferParameter :public RenderParameter {
	public:
		ConstantBufferParameter();
		virtual ~ConstantBufferParameter();

	public:		
		virtual const ParameterType GetParameterType() override;
		virtual void SetParameterData(void* pData, unsigned int theradID = 0) override;
	public: 
		int GetResourceIndex(unsigned int threadID);

	protected:
		int _iConstBuffers[NUM_THREADS + 1];
	};
}