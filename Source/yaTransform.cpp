#include "yaTransform.h"
#include "yaRenderer.h"

namespace ya
{
	Transform::Transform()
		:Component(eComponentType::Transform)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::FixedUpdate()
	{
		SetConstantBuffer();
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];

		Vector4 pos(mPosition.x, mPosition.y, mPosition.z, 0.0f);
		cb->Bind(&pos);
		cb->SetPipline(eShaderStage::VS);
	}


}