#pragma once
#include "yaResource.h"
#include "..\External\DirectXTex\Include\DirectXTex.h"
#include "yaGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib") 
#else 
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib") 
#endif

namespace ya
{
	class Texture : public Resource
	{
	public:		
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(graphics::eShaderStage stage, UINT slot);

		void Clear();

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;

	};
}
