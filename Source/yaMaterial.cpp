#include "yaMaterial.h"

namespace ya
{
	Material::Material()
		:Resource(eResourceType::Material)
	{
	}

	Material::~Material()
	{
	}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::SetData(eGPUParam type, void* data)
	{
		switch (type)
		{
		case ya::graphics::eGPUParam::Int:
			mCB.iData = *static_cast<int*>(data);
			break;
		case ya::graphics::eGPUParam::Float:
			mCB.fData = *static_cast<float*>(data);
			break;
		case ya::graphics::eGPUParam::Vector2:
			mCB.vector2= *static_cast<Vector2*>(data);
			break;
		case ya::graphics::eGPUParam::Vector3:
			mCB.vector3 = *static_cast<Vector3*>(data);
			break;
		case ya::graphics::eGPUParam::Vector4:
			mCB.vector4 = *static_cast<Vector4*>(data);
			break;
		case ya::graphics::eGPUParam::Matrix:
			mCB.matrix = *static_cast<Matrix*>(data);
			break;
		default:
			break;
		}
	}

	void Material::Bind()
	{
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Material];

		cb->Bind(&mCB);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);

		mShader->Binds();

	}

}