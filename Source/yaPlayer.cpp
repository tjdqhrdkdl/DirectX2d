#include "yaPlayer.h"
#include "yaPlayerScript.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
namespace ya
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{	
		Transform* playerTr = GetComponent<Transform>();
		playerTr->SetPosition(Vector3(3, 2, 10));

		SpriteRenderer* playerSr = AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> playerMesh = Resources::Find<Mesh>(L"RectMesh");
		shared_ptr<Material> playerMtr = Resources::Find<Material>(L"RectMaterial");
		playerSr->SetMaterial(playerMtr);
		playerSr->SetMesh(playerMesh);
		
		Collider2D* bodyCol = AddComponent<Collider2D>();
		bodyCol->SetType(eColliderType::Rect);

		Animator* animator = AddComponent<Animator>();
		shared_ptr<Texture> texture = Resources::Load<Texture>(L"playerTexture", L"20.01a - Character Base 2.5b//char_a_p4//char_a_p4_0bas_humn_v00.png");
		animator->Create(L"Idle", texture, Vector2(64, 256), Vector2(64, 64), Vector2::Zero, 2, 0.3f);
		animator->Play(L"Idle", true);

		AddComponent<PlayerScript>();

		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}