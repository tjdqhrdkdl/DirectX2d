#include "yaMagicBall.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"

#include "yaLight.h"
#include "yaTime.h"
#include "yaObject.h"


//objects
#include "yaPlayer.h"
namespace ya
{
	MagicBall::MagicBall()
		:mbActive(true)
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
		shared_ptr<Texture> atlasBlue = Resources::Load<Texture>(L"ElectricBallBlue", L"ElectricBall//ElectricBallBlue.png");
		shared_ptr<Texture> atlasRed = Resources::Load<Texture>(L"ElectricBallRed", L"ElectricBall//ElectricBallRed.png");
		shared_ptr<Texture> atlasYellow = Resources::Load<Texture>(L"ElectricBallYellow", L"ElectricBall//ElectricBallYellow.png");

		animator->Create(L"BlueIdle", atlasBlue, Vector2(0, 0), Vector2(50, 50), Vector2::Zero, 1, 0.3f);
		animator->Create(L"RedIdle", atlasRed, Vector2(0, 0), Vector2(50, 50), Vector2::Zero, 1, 0.3f);
		animator->Create(L"YellowIdle", atlasYellow, Vector2(0, 0), Vector2(50, 50), Vector2::Zero, 1, 0.3f);

		Light* lightComp = AddComponent<Light>();
		lightComp->SetType(eLightType::Point);
		lightComp->SetRadius(0.2f);

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

		lightComp->SetDiffuse(Vector4(1.0, 1.0f, 1.0, 1.0f));
	
	
	}

	void MagicBall::Update()
	{
		Revolove();
		Shine();
		Activate();
		GameObject::Update();
	}

	void MagicBall::FixedUpdate()
	{
		GameObject::FixedUpdate();

	}

	void MagicBall::Render()
	{
		if(mbActive)
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

	bool MagicBall::Shoot()
	{
		if (mbActive)
		{
			MagicBullet* bullet = object::Instantiate<MagicBullet>(eLayerType::PlayerProjectTile);
			bullet->Initialize();
			bullet->SetType(mType);
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			Vector2 dir = SceneManager::GetPlayScene()->GetMousePos() - Vector2(pos.x, pos.y);
			dir.Normalize();
			bullet->SetDir(Vector3(dir.x, dir.y, 10));
			bullet->GetComponent<Transform>()->SetPosition(Vector3(pos.x, pos.y, 10));
			mbHead = false;
			mbActive = false;
			return true;
		}
		else
			return false;
	}

	void MagicBall::Shine()
	{
		if (mbHead && mbActive)
		{
			if (mBrightness < 0.2f or mBrightness > 0.5f)
				mBrightness = 0.2f;
			if (mbLightUp)
			{
				mBrightness += 0.1 * Time::DeltaTime();
				if (mBrightness > 0.35f)
					mbLightUp = false;
			}
			else
			{
				mBrightness -= 0.1 * Time::DeltaTime();
				if (mBrightness < 0.2f)
					mbLightUp = true;
			}
		}
		else
			mBrightness = 0;
		GetComponent<Light>()->SetRadius(mBrightness);
	}

	void MagicBall::Activate()
	{
		if (!mbActive)
		{
			mActiveTimeChecker += Time::DeltaTime();
			if (mActiveTimeChecker > 8)
			{
				mActiveTimeChecker = 0;
				mbActive = true;
			}
		}
	}

	void MagicBall::SetPlayer(Player* pl)
	{
		mOwnerPlayer = pl;
		pl->AddBall(this);
		
	}

}