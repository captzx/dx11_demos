#pragma once
#include "PipeResource.h"

namespace insight {
	class PipeBuffer :public PipeResource {
	public:
		PipeBuffer();
		virtual ~PipeBuffer() {}

		ID3D11Resource* GetResource() override { return _pBuffer.Get(); }

		D3D11_BUFFER_DESC GetActualDescription();
		D3D11_BUFFER_DESC GetDesiredDescription() { return _desiredDesc; }
		void SetDesiredDescription(const D3D11_BUFFER_DESC& desc) { _desiredDesc = desc; }

		UINT GetByteWidth();
		void SetByteWidth(UINT ByteWidth) { _desiredDesc.ByteWidth = ByteWidth; }

		D3D11_USAGE GetUsage();
		void SetUsage(D3D11_USAGE Usage) { _desiredDesc.Usage = Usage; }
			 
		UINT GetBindFlags();
		void SetBindFlags(UINT BindFlags) { _desiredDesc.BindFlags = BindFlags; }
			 
		UINT GetCPUAccessFlags();
		void SetCPUAccessFlags(UINT CPUAccessFlags) { _desiredDesc.CPUAccessFlags = CPUAccessFlags; }
			 
		UINT GetMiscFlags();
		void SetMiscFlags(UINT MiscFlags) { _desiredDesc.MiscFlags = MiscFlags; }
			 
		UINT GetStructureByteStride();
		void SetStructureByteStride(UINT StructureByteStride) { _desiredDesc.StructureByteStride = StructureByteStride; }
			 
		void *Map() { return nullptr; }
		void UnMap() {}
	protected:
		ComPtr<ID3D11Buffer> _pBuffer;
		D3D11_BUFFER_DESC _desiredDesc;
		D3D11_BUFFER_DESC _actualDesc;
	};

	class VertexBuffer : public PipeBuffer{
	public:
		VertexBuffer(ComPtr<ID3D11Buffer> pBuffer) { _pBuffer = pBuffer; }
		virtual ~VertexBuffer() {}

		virtual PipeResourceType GetType() override { return PRT_VERTEXBUFFER; }

		void SetVertexSize(int size) { _iVertexSize = size; }
		void SetVertexCount(int count) { _iVertexCount = count; }

	protected:
		int	_iVertexSize;
		int	_iVertexCount;
	};

	class IndexBuffer : public PipeBuffer {
	public:
		IndexBuffer(ComPtr<ID3D11Buffer> pBuffer) { _pBuffer = pBuffer; }
		virtual ~IndexBuffer() {}

		virtual PipeResourceType GetType() override { return PRT_INDEXBUFFER; }

		void SetIndexSize(int size) { _iIndexSize = size; }
		void SetIndexCount(int count) { _iIndexCount = count; }

	protected:
		int _iIndexSize;
		int _iIndexCount;
	};

	class RenderingPipeline;
	class RenderParameter;
	struct ConstantBufferMapping{
		RenderParameter* pParameter;
		unsigned int Offset;
		unsigned int Size;
		D3D_SHADER_VARIABLE_CLASS VariableClass;
		unsigned int Elements;
		unsigned int ValueID;
	};

	class IParameterManager;
	class ConstantBuffer : public PipeBuffer {
	public:
		ConstantBuffer(ComPtr<ID3D11Buffer> pBuffer):
			_bAutoUpdate(true) { 
			_pBuffer = pBuffer;
		}
		virtual ~ConstantBuffer() {}

		virtual PipeResourceType GetType() override { return PRT_CONSTANTBUFFER; }
		void AddMapping(ConstantBufferMapping& mapping);
		void EmptyMappings();
		void EvaluateMappings(RenderingPipeline* pPipeline, IParameterManager* pParamManager);
		bool ContainsMapping(int index, const ConstantBufferMapping& mapping);
			 
		void SetAutoUpdate(bool enable);
		bool GetAutoUpdate();

	protected:
		bool _bAutoUpdate;
		std::vector<ConstantBufferMapping> _vConstantBufferMappings;
	};
}