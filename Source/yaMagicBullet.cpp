#include "yaMagicBullet.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider2D.h"

#include "yaLight.h"
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
		shared_ptr<Texture> atlas = Resources::Load<Texture>(L"ElectricBall", L"ElectricBall//ElectricBall.png");

		animator->Create(L"Idle", atlas, Vector2(0, 0), Vector2(50, 50), Vector2::Zero, 1, 0.3f);

		animator->Play(L"Idle", false);

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
			colObj->SetSize(colObj->GetSize() - 0.3f);
			SetDead();
		}
	}

	void MagicBullet::OnCollisionStay(Collider2D* col)
	{
	}

	void MagicBullet::OnCollisionExit(Collider2D* col)
	{
	}

}