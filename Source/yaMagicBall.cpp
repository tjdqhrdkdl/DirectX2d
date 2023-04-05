#include "yaMagicBall.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"

#include "yaLight.h"
#include "yaTime.h"
#include "yaObject.h"
namespace ya
{
	MagicBall::MagicBall()
	{
	}

	MagicBall::~MagicBall()
	{
	}

	void MagicBall::Initialize()
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
	
	
	}

	void MagicBall::Update()
	{
		Revolove();
		Shine();
		GameObject::Update();
	}

	void MagicBall::FixedUpdate()
	{
		GameObject::FixedUpdate();

	}

	void MagicBall::Render()
	{
		GameObject::Render();

	}

	void MagicBall::Revolove()
	{
		mTheta += 2*Time::DeltaTime();

		if (mTheta > XM_2PI)
			mTheta = 0;

		Transform* plTr = mOwnerPlayer->GetComponent<Transform>();
		Vector3 plPos = plTr->GetPosition();
		mPos = Vector3(-cosf(mTheta)/2, -sinf(mTheta)/6, -sinf(mTheta)/3);

		GetComponent<Transform>()->SetPosition(plPos + mPos);
	}

	void MagicBall::Shoot()
	{
		MagicBullet* bullet = object::Instantiate<MagicBullet>(eLayerType::PlayerProjectTile);
		bullet->Initialize();
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector2 dir = SceneManager::GetPlayScene()->GetMousePos() - Vector2(pos.x, pos.y);
		dir.Normalize();
		bullet->SetDir(Vector3(dir.x,dir.y,10));
		bullet->GetComponent<Transform>()->SetPosition(Vector3(pos.x,pos.y,10));
	}

	void MagicBall::Shine()
	{
		if (mBrightness < 0.2f or mBrightness > 0.5f)
			mBrightness = 0.2f;
		if(mbLightUp)
		{
			mBrightness += 0.1*Time::DeltaTime();
			if (mBrightness > 0.35f)
				mbLightUp = false;
		}
		else
		{
			mBrightness -= 0.1 * Time::DeltaTime();
			if (mBrightness < 0.2f)
				mbLightUp = true;
		}
		GetComponent<Light>()->SetRadius(mBrightness);
	}

}