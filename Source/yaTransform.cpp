#include "yaTransform.h"
#include "yaRenderer.h"
#include "yaGameObject.h"
#include "yaCamera.h"
#include "yaMaterial.h"
namespace ya
{
	Transform::Transform()
		:Component(eComponentType::Transform)
		,mForward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
		, mScale(Vector3::One)
		, mRotation(Vector3::Zero)
		, mPosition(Vector3::One)
		, mParent(nullptr)
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

		//크기 회전 이동 행렬 만들기
		Matrix scale = Matrix::CreateScale(mScale);

		// 회전 변환 행렬
		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);


		// 이동 변환 행렬
		Matrix position;
		position.Translation(mPosition);

		mWorldMatrix = scale * rotation * position;

		//국소 좌표계를 기억하기 위해 저장
		mForward = Vector3::Transform(Vector3::Forward, rotation);
		mUp = Vector3::Transform(Vector3::Up, rotation);
		mRight = Vector3::Transform(Vector3::Right, rotation);

		if (mParent != nullptr)
		{
			mWorldMatrix *= mParent->mWorldMatrix;
		}

	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		// bind는 한번 해줘야하는데, 버퍼 정보는 카메라와 트랜스폼에 나누어져 있음.
		renderer::TransformCB trCb = {};
		trCb.world = mWorldMatrix;
		trCb.view = Camera::GetGpuViewMatrix();
		trCb.projection = Camera::GetGpuProjectionMatrix();


		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->Bind(&trCb);
		cb->SetPipline(eShaderStage::VS);		
		
	}


}