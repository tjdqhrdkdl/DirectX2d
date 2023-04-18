#include "yaRigidBody.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaTransform.h"
namespace ya
{
	Rigidbody::Rigidbody()
		:Component(eComponentType::Rigidbody)
		, mMass(100.0f)
		, mFriction(50.0f)
		, mbGround(false)
	{

		mGravity = Vector3(0.0f, -15.0f , 0.0f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{

		if (mbGround)
		{
			// ������ ������
			mVelocity.y = 0;
		}
		else
		{
			// ���߿� ���� ��
			mVelocity += mGravity * Time::DeltaTime();
		}
		//�̵�
// F = M x A
// A = F / M
		mAccelation = mForce / (mMass/100);

		// �ӵ��� ���ӵ��� ���Ѵ�
		mVelocity += mAccelation;

		// �ִ� �ӵ� ����
		//Vector2 gravity = mGravity;
		//gravity.Normalize();
		//float dot = ya::math::Dot(mVelocity, gravity);
		//gravity = gravity * dot;

		//Vector2 sideVelocity = mVelocity - gravity;
		//if (mLimitVelocity.y < gravity.Length())
		//{
		//	gravity.Normalize();
		//	gravity *= mLimitVelocity.y;
		//}

		//if (mLimitVelocity.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitVelocity.x;
		//}
		//mVelocity = gravity + sideVelocity;

		//������ ���� ( ����� ���� ����, �ӵ��� 0 �� �ƴ� ��)
		if (!(mVelocity == Vector3::Zero) )
		{
			// �ӵ��� �ݴ� �������� �������� ����
			Vector3 friction = -mVelocity;
			friction.Normalize();
			friction.x = friction.x * mFriction * (mMass/100) * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
			if (abs(mVelocity.x) < abs(friction.x))
			{
				// �ӵ��� 0 �� �����.
				mVelocity.x = 0;
			}
			else
			{
				// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
				mVelocity.x += friction.x;
			}
		}

		// �ӵ��� �°� ��ü�� �̵���Ų��.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);
		mForce = Vector3::Zero;

		if (mbPushed && mbGround && mVelocity == Vector3::Zero)
		{
			mbPushed = false;
		}
	}

	void Rigidbody::FixedUpdate()
	{
	}

	void Rigidbody::Render()
	{
	}

}