#pragma once
#include "yaResource.h"
#include "yaRenderer.h"
#include "yaShader.h"

using namespace ya::renderer;
namespace ya
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam type, void* data);
		void Bind();

		void SetShader(Shader* shader) { mShader = shader; }
		Shader* GetShader() { return mShader; }

	private:
		Shader* mShader;
		MaterialCB mCB;

	};
}

