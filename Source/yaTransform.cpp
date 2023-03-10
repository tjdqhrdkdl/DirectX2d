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

		//ũ�� ȸ�� �̵� ��� �����
		Matrix scale = Matrix::CreateScale(mScale);

		// ȸ�� ��ȯ ���
		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);


		// �̵� ��ȯ ���
		Matrix position;
		position.Translation(mPosition);

		mWorldMatrix = scale * rotation * position;

		//���� ��ǥ�踦 ����ϱ� ���� ����
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
		// bind�� �ѹ� ������ϴµ�, ���� ������ ī�޶�� Ʈ�������� �������� ����.
		renderer::TransformCB trCb = {};
		trCb.world = mWorldMatrix;
		trCb.view = Camera::GetGpuViewMatrix();
		trCb.projection = Camera::GetGpuProjectionMatrix();


		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->Bind(&trCb);
		cb->SetPipline(eShaderStage::VS);		
		
	}


}