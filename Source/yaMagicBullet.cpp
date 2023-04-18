#include "yaMagicBullet.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"
#include "yaAnimator.h"
#include "yaCollider2D.h"
#include "yaRigidBody.h"
#include "yaLight.h"


#include "yaResources.h"
#include "yaTime.h"
#include "yaObject.h"

namespace ya
{
	MagicBullet::MagicBullet()
		:mSpeed(5.0f)
		,mAliveTime(5.0f)
		,mAliveTimeChecker(0)
	{
	}

	MagicBullet::~MagicBullet()
	{
	}

	void MagicBullet::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(0.2, 0.2, 1));

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"CircleMesh");
		shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);

		Animator* animator = AddComponent<Animator>();
		shared_ptr<Texture> atlasBlue = Resources::Find<Texture>(L"ElectricBallBlue");
		shared_ptr<Texture> atlasRed =  Resources::Find<Texture>(L"ElectricBallRed");
		shared_ptr<Texture> atlasYellow= Resources::Find<Texture>(L"ElectricBallYellow");

		animator->Create(L"BlueIdle", atlasBlue, Vector2(0, 0), Vector2(50, 50), Vector2::Zero, 1, 0.3f);
		animator->Create(L"RedIdle", atlasRed, Vector2(0, 0), Vector2(50, 50), Vector2::Zero, 1, 0.3f);
		animator->Create(L"YellowIdle", atlasYellow, Vector2(0, 0), Vector2(50, 50), Vector2::Zero, 1, 0.3f);

		animator->Play(L"BlueIdle", false);

		Light* lightComp = AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(0.2f);
		lightComp->SetDiffuse(Vector4(0, 1.0f, 0, 1.0f));
		
		Collider2D* col = AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		GameObject::Initialize();

	}

	void MagicBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos += mDir * mSpeed * Time::DeltaTime();
		tr->SetPosition(pos);

		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
			SetDead();
		GameObject::Update();
	}

	void MagicBullet::FixedUpdate()
	{
		GameObject::FixedUpdate();

	}

	void MagicBullet::Render()
	{
		GameObject::Render();

	}

	void MagicBullet::OnCollisionEnter(Collider2D* col)
	{
		GameObject* colObj = col->GetOwner();
		if (colObj->GetLayerType() == eLayerType::Ground)
		{

		}
		else
		{
			Rigidbody* colRb = colObj->GetComponent<Rigidbody>();
			switch (mType)
			{
			case eMagicBulletType::XBall:
				colRb->PushX(20);
				break;
			case eMagicBulletType::YBall:
				colRb->PushY(10);
				break;
			case eMagicBulletType::ZBall:
				colObj->SetSize(colObj->GetSize() - 1.0f);
				break;
			default:
				break;
			}
			SetDead();
		}
	}

	void MagicBullet::OnCollisionStay(Collider2D* col)
	{
	}

	void MagicBullet::OnCollisionExit(Collider2D* col)
	{
	}

	void MagicBullet::SetType(eMagicBulletType type)
	{
		Animator* animator = GetComponent<Animator>();
		mType = type;
		switch (mType)
		{
		case ya::MagicBullet::eMagicBulletType::None:
			break;
		case ya::MagicBullet::eMagicBulletType::XBall:
			animator->Play(L"RedIdle", false);
			break;
		case ya::MagicBullet::eMagicBulletType::YBall:
			animator->Play(L"YellowIdle", false);
			break;
		case ya::MagicBullet::eMagicBulletType::ZBall:
			animator->Play(L"BlueIdle", false);
			break;
		default:
			break;
		}
	}

}