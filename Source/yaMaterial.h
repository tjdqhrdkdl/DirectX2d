#pragma once
#include "yaResource.h"
#include "yaRenderer.h"
#include "yaShader.h"
#include "yaTexture.h"

using namespace ya::renderer;
using namespace ya::graphics;
using namespace std;

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

		void SetShader(shared_ptr<Shader> shader) { mShader = shader; }
		shared_ptr<Shader> GetShader() { return mShader; }
		void SetTexture(shared_ptr<Texture> texture) { mTexture = texture; }
		shared_ptr<Texture> GetTexture() { return mTexture; }

		eRenderingMode GetRenderingMode() { return mMode; }
		void SetRenderingMode(eRenderingMode mode) { mMode = mode;}

		void Clear();
	private:
		shared_ptr<Texture> mTexture;
		shared_ptr<Shader> mShader;
		MaterialCB mCB;

		eRenderingMode mMode;

	};
}

