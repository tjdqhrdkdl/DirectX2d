#include "yaPlayerScript.h"
#include "yaGameObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaRigidBody.h"
#define STATE_HAVE(STATE) (mState & STATE) == STATE
#define ADD_STATE(STATE) mState |= STATE
#define RM_STATE(STATE) mState &= ~STATE
namespace ya
{
	PlayerScript::PlayerScript()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{	
		
		Transform* playerTr = GetOwner()->GetComponent<Transform>();
		playerTr->SetPosition(Vector3(0, 3, 10));
		playerTr->SetScale(Vector3(2, 2, 1));

		SpriteRenderer* playerSr = GetOwner()->AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> playerMesh = Resources::Find<Mesh>(L"RectMesh");
		shared_ptr<Material> playerMtr = Resources::Find<Material>(L"RectMaterial");
		playerSr->SetMaterial(playerMtr);
		playerSr->SetMesh(playerMesh);
		
		Collider2D* bodyCol = GetOwner()->AddComponent<Collider2D>();
		bodyCol->SetType(eColliderType::Rect);
		bodyCol->SetSize(Vector2(0.2, 0.45));
		bodyCol->SetCenter(Vector2(0,0.05));
		bodyCol->SetJumpBox(false);
		bodyCol->Initialize();

		Collider2D* jumpCol = GetOwner()->AddComponent<Collider2D>();
		jumpCol->SetType(eColliderType::Rect);
		jumpCol->SetSize(Vector2(0.05, 0.05));
		jumpCol->SetCenter(Vector2(0, -0.4));
		bodyCol->SetJumpBox(true);
		jumpCol->Initialize();

		mRigidbody = GetOwner()->AddComponent<Rigidbody>();

		mAnimator = GetOwner()->AddComponent<Animator>();
		shared_ptr<Texture> baseTexture1 = Resources::Load<Texture>(L"playerBaseTexture1", L"20.01a - Character Base 2.5b//char_a_p1//char_a_p1_0bas_humn_v00.png");
		shared_ptr<Texture> baseTexture2 = Resources::Load<Texture>(L"playerBaseTexture2", L"20.01a - Character Base 2.5b//char_a_p2//char_a_p2_0bas_humn_v00.png");
		shared_ptr<Texture> baseTexture3 = Resources::Load<Texture>(L"playerBaseTexture3", L"20.01a - Character Base 2.5b//char_a_p3//char_a_p3_0bas_humn_v00.png");
		shared_ptr<Texture> baseTexture4 = Resources::Load<Texture>(L"playerBaseTexture4", L"20.01a - Character Base 2.5b//char_a_p4//char_a_p4_0bas_humn_v00.png");
		
		shared_ptr<Texture> attackTexture = Resources::Load<Texture>(L"attackTexture", L"21.07b - Sword & Shield Combat 2.3//char_a_pONE3//char_a_pONE3_0bas_humn_v00.png");

		mAnimator->Create(L"Idle", baseTexture4, Vector2(64, 256), Vector2(64, 64), Vector2::Zero, 2, 0.3f);
		mAnimator->Create(L"Walk", baseTexture1, Vector2(0, 384), Vector2(64, 64), Vector2::Zero, 6, 0.1f);
		mAnimator->Create(L"Run", baseTexture1, Vector2(384, 384), Vector2(64, 64), Vector2::Zero, 2, 0.1f);
		mAnimator->Create(L"JumpUp", baseTexture1, Vector2(64*5, 128), Vector2(64, 64), Vector2::Zero, 2, 0.1f);
		mAnimator->Create(L"JumpDown", baseTexture1, Vector2(64*7, 128), Vector2(64, 64), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Attack", attackTexture, Vector2(0, 64*2), Vector2(64, 64), Vector2::Zero, 4, 0.1f);


		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&PlayerScript::AttackCompleteEvent, this);

		mAnimator->Play(L"Idle", true);

		Script::Initialize();
	}

	void PlayerScript::Update()
	{
		SetState();
		SetAnimation();
		Move();
		Attack();
		Jump();
		Script::Update();
	}

	void PlayerScript::FixedUpdate()
	{
		Script::FixedUpdate();
	}

	void PlayerScript::Render()
	{
		Script::Render();
	}

	void PlayerScript::SetState()
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
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			if (!(STATE_HAVE(PlayerState_Attack)))
			{
				if (!(STATE_HAVE(PlayerState_Jump)))
				{
					ADD_STATE(PlayerState_Jump);

					Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
					rb->SetGround(false);
					rb->AddForce(Vector3(0, 8, 0));
				}
			}
		}		
		
		if (Input::GetKeyDown(eKeyCode::R))
		{
			ADD_STATE(PlayerState_Attack);
			if (STATE_HAVE(PlayerState_Jump))
				;
			else
			{
				RM_STATE(PlayerState_Walk);
				RM_STATE(PlayerState_Run);
			}
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(0, 2, 0));
		}
	}

	void PlayerScript::SetAnimation()
	{
		std::wstring prevName = mAnimator->GetPlayAnimation()->GetAnimationName();
		std::wstring animName;
		bool loop = true;

		if (STATE_HAVE(ePlayerState::PlayerState_Attack))
			animName = L"Attack";
		else if (STATE_HAVE(ePlayerState::PlayerState_Jump) && mRigidbody->isFalling())
			animName = L"JumpDown", loop = false;
		else if (STATE_HAVE(ePlayerState::PlayerState_Jump))
			animName = L"JumpUp", loop = false;
		else if (STATE_HAVE(ePlayerState::PlayerState_Walk))
			animName = L"Walk";
		else if (STATE_HAVE(ePlayerState::PlayerState_Run))
			animName = L"Run";
		else
			animName = L"Idle";

		if (STATE_HAVE(ePlayerState::PlayerState_LookRight))
			mAnimator->SetReverse(false);
		else
			mAnimator->SetReverse(true);

		if(prevName != animName)
			mAnimator->Play(animName,loop);
	}

	void PlayerScript::Move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
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

	void PlayerScript::Attack()
	{
	}

	void PlayerScript::Jump()
	{
		if (mRigidbody->isGround())
			RM_STATE(PlayerState_Jump);
	}

	void PlayerScript::Fall()
	{
		mRigidbody->SetGround(false);
		ADD_STATE(PlayerState_Jump);
	}

	void PlayerScript::AttackCompleteEvent()
	{
		RM_STATE(PlayerState_Attack);
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

}