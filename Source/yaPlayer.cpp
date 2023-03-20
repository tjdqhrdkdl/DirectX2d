#include "yaPlayer.h"
#include "yaPlayerScript.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaInput.h"
#define STATE_HAVE(STATE) (mState & STATE) == STATE
#define ADD_STATE(STATE) mState |= STATE
#define RM_STATE(STATE) mState &= ~STATE
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
		playerTr->SetPosition(Vector3(3, 0,5));

		SpriteRenderer* playerSr = AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> playerMesh = Resources::Find<Mesh>(L"RectMesh");
		shared_ptr<Material> playerMtr = Resources::Find<Material>(L"RectMaterial");
		playerSr->SetMaterial(playerMtr);
		playerSr->SetMesh(playerMesh);
		
		Collider2D* bodyCol = AddComponent<Collider2D>();
		bodyCol->SetType(eColliderType::Rect);

		mAnimator = AddComponent<Animator>();
		shared_ptr<Texture> texture1 = Resources::Load<Texture>(L"playerTexture1", L"20.01a - Character Base 2.5b//char_a_p1//char_a_p1_0bas_humn_v00.png");
		shared_ptr<Texture> texture2 = Resources::Load<Texture>(L"playerTexture2", L"20.01a - Character Base 2.5b//char_a_p2//char_a_p2_0bas_humn_v00.png");
		shared_ptr<Texture> texture3 = Resources::Load<Texture>(L"playerTexture3", L"20.01a - Character Base 2.5b//char_a_p3//char_a_p3_0bas_humn_v00.png");
		shared_ptr<Texture> texture4 = Resources::Load<Texture>(L"playerTexture4", L"20.01a - Character Base 2.5b//char_a_p4//char_a_p4_0bas_humn_v00.png");
		mAnimator->Create(L"Idle", texture4, Vector2(64, 256), Vector2(64, 64), Vector2::Zero, 2, 0.3f);
		mAnimator->Create(L"WalkRight", texture1, Vector2(0, 384), Vector2(64, 64), Vector2::Zero, 6, 0.1f);
		mAnimator->Create(L"WalkLeft", texture1, Vector2(0, 448), Vector2(64, 64), Vector2::Zero, 6, 0.1f);
		mAnimator->Create(L"RunRight", texture1, Vector2(384, 384), Vector2(64, 64), Vector2::Zero, 2, 0.1f);
		mAnimator->Create(L"RunLeft", texture1, Vector2(384, 448), Vector2(64, 64), Vector2::Zero, 2, 0.1f);
		mAnimator->Play(L"Idle", true);

		AddComponent<PlayerScript>();

		GameObject::Initialize();
	}

	void Player::Update()
	{
		SetState();
		SetAnimation();
		Move();
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

	void Player::SetState()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			if (!(STATE_HAVE(PlayerState_Attack)))
			{
				RM_STATE(PlayerState_LookRight);
				ADD_STATE(PlayerState_Walk);
			}
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			RM_STATE(PlayerState_Walk);
			RM_STATE(PlayerState_Run);
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			if (!(STATE_HAVE(PlayerState_Attack)))
			{
				ADD_STATE(PlayerState_LookRight);
				ADD_STATE(PlayerState_Walk);
			}
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			RM_STATE(PlayerState_Walk);
			RM_STATE(PlayerState_Run);
		}
		if (Input::GetKey(eKeyCode::LSHIFT))
		{
			if ((STATE_HAVE(PlayerState_Walk)))
			{
				RM_STATE(PlayerState_Walk);
				ADD_STATE(PlayerState_Run);
			}
		}
	}

	void Player::SetAnimation()
	{
		std::wstring prevName = mAnimator->GetPlayAnimation()->GetAnimationName();
		std::wstring animName;
		if (STATE_HAVE(ePlayerState::PlayerState_LookRight))
		{
			if (STATE_HAVE(ePlayerState::PlayerState_Attack))
				animName = L"AttackRight";
			else if (STATE_HAVE(ePlayerState::PlayerState_Jump))
				animName = L"JumpRight";
			else if (STATE_HAVE(ePlayerState::PlayerState_Walk))
				animName = L"WalkRight";
			else if (STATE_HAVE(ePlayerState::PlayerState_Run))
				animName = L"RunRight";
			else
				animName = L"Idle";
		}
		else
		{
			if (STATE_HAVE(ePlayerState::PlayerState_Attack))
				animName = L"AttackLeft";
			else if (STATE_HAVE(ePlayerState::PlayerState_Jump))
				animName = L"JumpLeft";
			else if (STATE_HAVE(ePlayerState::PlayerState_Walk))
				animName = L"WalkLeft";
			else if (STATE_HAVE(ePlayerState::PlayerState_Run))
				animName = L"RunLeft";
			else
				animName = L"Idle";
		}
		if(prevName != animName)
			mAnimator->Play(animName);
	}

	void Player::Move()
	{
		Transform* tr = GetComponent<Transform>();
		if (STATE_HAVE(PlayerState_Walk))
		{
			if (STATE_HAVE(PlayerState_LookRight))
			{
				Vector3 pos = tr->GetPosition();
				pos.x += 3.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else
			{
				Vector3 pos = tr->GetPosition();
				pos.x -= 3.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}
		else if (STATE_HAVE(PlayerState_Run))
		{

			if (STATE_HAVE(PlayerState_LookRight))
			{
				Vector3 pos = tr->GetPosition();
				pos.x += 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
			else
			{
				Vector3 pos = tr->GetPosition();
				pos.x -= 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);
			}
		}

	}

}