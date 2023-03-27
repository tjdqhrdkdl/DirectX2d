#include "yaMagicBallScript.h"
#include "yaGameObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaRigidBody.h"

namespace ya
{
	MagicBallScript::MagicBallScript()
	{
	}

	MagicBallScript::~MagicBallScript()
	{
	}

	void MagicBallScript::Initialize()
	{
		Transform* ballTr = GetOwner()->GetComponent<Transform>();
		ballTr->SetPosition(Vector3::Zero);
		ballTr->SetScale(Vector3(0.2, 0.2, 1));

		SpriteRenderer* ballSr = GetOwner()->AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> ballMesh = Resources::Find<Mesh>(L"CircleMesh");
		shared_ptr<Material> ballMtr = Resources::Find<Material>(L"RectMaterial");
		ballSr->SetMaterial(ballMtr);
		ballSr->SetMesh(ballMesh);

		
	}

	void MagicBallScript::Update()
	{
		Transform* ballTr = GetOwner()->GetComponent<Transform>();
		mTheta += 2 * Time::DeltaTime();
		if (mTheta > XM_2PI)
			mTheta = 0;
		Vector3 pos = mPlayer->GetComponent<Transform>()->GetPosition();
		pos += Vector3(0.03f, 0, 0.5f);
		mPos += Vector3(cos(mTheta) * Time::DeltaTime(), 0, -sin(mTheta) * Time::DeltaTime());
		ballTr->SetPosition(pos + mPos);
		Script::Update();
	}

	void MagicBallScript::FixedUpdate()
	{
		Script::FixedUpdate();

	}

	void MagicBallScript::Render()
	{
		Script::Render();

	}

	void MagicBallScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void MagicBallScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void MagicBallScript::OnCollisionExit(Collider2D* collider)
	{
	}

}