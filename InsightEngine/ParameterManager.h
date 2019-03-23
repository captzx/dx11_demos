#pragma once

namespace insight {
	class RenderParameter;
	class MatrixParameter;
	class ConstantBufferParameter;
	class PipeResourceProxy;

	class IParameterManager {
	public:
		IParameterManager() {};
		virtual ~IParameterManager() {};

		virtual unsigned int GetID() = 0;

		virtual void SetMatrixParameter(const std::wstring& name, XMFLOAT4X4* pMatrix) = 0;
		virtual void SetConstantBufferParameter(const std::wstring& name, std::shared_ptr<PipeResourceProxy> resource) = 0;

		virtual void SetMatrixParameter(RenderParameter* pParameter, XMFLOAT4X4* pMatrix) = 0;
		virtual void SetConstantBufferParameter(RenderParameter* pParameter, std::shared_ptr<PipeResourceProxy> resource) = 0;

		virtual RenderParameter* GetRenderParameterRef(const std::wstring& name) = 0;
		virtual MatrixParameter* GetMatrixParameterRef(const std::wstring name) = 0;
		virtual ConstantBufferParameter* GetConstantBufferParameterRef(const std::wstring name) = 0;

		virtual XMMATRIX GetMatrixParameter(RenderParameter* pParameter) = 0;
		virtual int GetConstantBufferParameter(RenderParameter* pParameter) = 0;

		virtual XMMATRIX GetMatrixParameter(const std::wstring name) = 0;
		virtual int GetConstantBufferParameter(const std::wstring name) = 0;

		virtual void SetWorldMatrixParameter(XMFLOAT4X4* pMatrix) = 0;
		virtual void SetViewMatrixParameter(XMFLOAT4X4* pMatrix) = 0;
		virtual void SetProjMatrixParameter(XMFLOAT4X4* pMatrix) = 0;
	};

	class ParameterManager: public IParameterManager {
	public:
		ParameterManager(unsigned int id);
		virtual ~ParameterManager();

	public:
		virtual unsigned int GetID() override;

		virtual void SetMatrixParameter(const std::wstring& name, XMFLOAT4X4* pMatrix) override;
		virtual void SetMatrixParameter(RenderParameter* pParameter, XMFLOAT4X4* pMatrix) override;
		virtual void SetConstantBufferParameter(const std::wstring& name, std::shared_ptr<PipeResourceProxy> resource) override;
		virtual void SetConstantBufferParameter(RenderParameter* pParameter, std::shared_ptr<PipeResourceProxy> resource) override;

		virtual RenderParameter* GetRenderParameterRef(const std::wstring& name) override;
		virtual MatrixParameter* GetMatrixParameterRef(const std::wstring name) override;
		virtual ConstantBufferParameter* GetConstantBufferParameterRef(const std::wstring name) override;
		
		virtual XMMATRIX GetMatrixParameter(RenderParameter* pParameter) override;
		virtual int GetConstantBufferParameter(RenderParameter* pParameter) override;

		virtual XMMATRIX GetMatrixParameter(const std::wstring name) override;
		virtual int GetConstantBufferParameter(const std::wstring name) override;

		virtual void SetWorldMatrixParameter(XMFLOAT4X4* pMatrix) override;
		virtual void SetViewMatrixParameter(XMFLOAT4X4* pMatrix) override;
		virtual void SetProjMatrixParameter(XMFLOAT4X4* pMatrix) override;

	protected:
		IParameterManager* _pParentManager;
		unsigned int _uID;

		MatrixParameter* _pWorldMatrix;
		MatrixParameter* _pViewMatrix;
		MatrixParameter* _pProjMatrix;

	public:
		static std::map<std::wstring, RenderParameter*>	sParameterMap;
	};
}