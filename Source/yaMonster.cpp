#include "yaMonster.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider2D.h"
#include "yaRigidbody.h"

#include "yaTime.h"
#include "yaObject.h"

namespace ya
{
	Monster::Monster()
	{
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		mBaseScale = Vector3(4.0f, 4.0f, 1);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(4.0f, 4.0f, 1));

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);

		Animator* animator = AddComponent<Animator>();
		shared_ptr<Texture> atlas = Resources::Load<Texture>(L"FlyingEye", L"Monster//Flying eye//Flight.png");

		animator->Create(L"Idle", atlas, Vector2(0, 0), Vector2(150, 150), Vector2::Zero, 8, 0.1f);

		animator->Play(L"Idle");


		Collider2D* col = AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.25,0.25));

		AddComponent<Rigidbody>();

		GameObject::Initialize();
	}

	void Monster::Update()
	{
		GameObject::Update();
	}

	void Monster::FixedUpdate()
	{
		GameObject::FixedUpdate();

	}

	void Monster::Render()
	{
		GameObject::Render();
	}

}