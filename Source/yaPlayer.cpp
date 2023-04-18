#include "yaPlayer.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaRigidBody.h"
#include "yaCollider2D.h"

#include "yaTime.h"
#include "yaInput.h"

#include "yaMagicBall.h"

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
		mBaseScale = Vector3(2, 2, 1);
		Transform* playerTr = GetComponent<Transform>();
		playerTr->SetPosition(Vector3(0, 5, 10));
		playerTr->SetScale(Vector3(2, 2, 1));

		SpriteRenderer* playerSr = AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> playerMesh = Resources::Find<Mesh>(L"RectMesh");
		shared_ptr<Material> playerMtr = Resources::Find<Material>(L"RectMaterial");
		playerSr->SetMaterial(playerMtr);
		playerSr->SetMesh(playerMesh);
		
		Collider2D* bodyCol = AddComponent<Collider2D>();
		bodyCol->SetType(eColliderType::Rect);
		bodyCol->SetSize(Vector2(0.2, 0.45));
		bodyCol->SetCenter(Vector2(0,0));
		bodyCol->SetJumpBox(false);
		bodyCol->Initialize();

		Collider2D* jumpCol = AddComponent<Collider2D>();
		jumpCol->SetType(eColliderType::Rect);
		jumpCol->SetSize(Vector2(0.2, 0.05));
		jumpCol->SetCenter(Vector2(0, -0.4));
		bodyCol->SetJumpBox(true);
		jumpCol->Initialize();

		mRigidbody = AddComponent<Rigidbody>();

		mAnimator = AddComponent<Animator>();
		shared_ptr<Texture> baseTexture1 = Resources::Load<Texture>(L"playerBaseTexture1", L"Character//20.01a - Character Base 2.5b//char_a_p1//char_a_p1_0bas_humn_v00.png");
		shared_ptr<Texture> baseTexture2 = Resources::Load<Texture>(L"playerBaseTexture2", L"Character//20.01a - Character Base 2.5b//char_a_p2//char_a_p2_0bas_humn_v00.png");
		shared_ptr<Texture> baseTexture3 = Resources::Load<Texture>(L"playerBaseTexture3", L"Character//20.01a - Character Base 2.5b//char_a_p3//char_a_p3_0bas_humn_v00.png");
		shared_ptr<Texture> baseTexture4 = Resources::Load<Texture>(L"playerBaseTexture4", L"Character//20.01a - Character Base 2.5b//char_a_p4//char_a_p4_0bas_humn_v00.png");
		
		shared_ptr<Texture> attackTexture = Resources::Load<Texture>(L"attackTexture", L"Character//21.07b - Sword & Shield Combat 2.3//char_a_pONE3//char_a_pONE3_0bas_humn_v01.png");

		mAnimator->Create(L"Idle", baseTexture4, Vector2(64, 256), Vector2(64, 64), Vector2::Zero, 2, 0.3f);
		mAnimator->Create(L"Walk", baseTexture1, Vector2(0, 384), Vector2(64, 64), Vector2::Zero, 6, 0.1f);
		mAnimator->Create(L"Run", baseTexture1, Vector2(384, 384), Vector2(64, 64), Vector2::Zero, 2, 0.1f);
		mAnimator->Create(L"JumpUp", baseTexture1, Vector2(64*5, 128), Vector2(64, 64), Vector2::Zero, 2, 0.1f);
		mAnimator->Create(L"JumpDown", baseTexture1, Vector2(64*7, 128), Vector2(64, 64), Vector2::Zero, 1, 0.1f);
		mAnimator->Create(L"Attack", attackTexture, Vector2(0, 64*2), Vector2(64, 64), Vector2::Zero, 4, 0.1f);


		mAnimator->GetCompleteEvent(L"Attack") = std::bind(&Player::AttackCompleteEvent, this);

		mAnimator->Play(L"Idle", true);

		GameObject::Initialize();
	}

	void Player::Update()
	{
		SetState();
		SetAnimation();
		Move();
		Attack();
		Jump();
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
		if (Input::GetKey(eKeyCode::A))
		{
			if (!(STATE_HAVE(PlayerState_Attack)))
			{
				RM_STATE(PlayerState_LookRight);
				ADD_STATE(PlayerState_Walk);
			}
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			RM_STATE(PlayerState_Walk);
			RM_STATE(PlayerState_Run);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			if (!(STATE_HAVE(PlayerState_Attack)))
			{
				ADD_STATE(PlayerState_LookRight);
				ADD_STATE(PlayerState_Walk);
			}
		}
		if (Input::GetKeyUp(eKeyCode::D))
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

					Rigidbody* rb = GetComponent<Rigidbody>();
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
			GetComponent<Transform>()->SetPosition(Vector3(0, 2, 10));
		}

		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			Shoot();
		}
	}

	void Player::SetAnimation()
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

	void Player::Attack()
	{
	}

	void Player::Shoot()
	{
		if (mHeadBall->Shoot())
		{
			if (++mHeadNum > mBalls.size() - 1)
				mHeadNum = 0;
			SetHeadBall(mBalls[mHeadNum]);
		}
	}

	void Player::Jump()
	{
		if (mRigidbody->isGround())
			RM_STATE(PlayerState_Jump);
	}

	void Player::Fall()
	{
		mRigidbody->SetGround(false);
		ADD_STATE(PlayerState_Jump);
	}

	void Player::AttackCompleteEvent()
	{
		RM_STATE(PlayerState_Attack);
	}

	void Player::SetHeadBall(MagicBall* ball)
	{ 
		mHeadBall = ball;
		ball->SetHead(true);
	}

	void Player::OnCollisionEnter(Collider2D* collider)
	{
	}

	void Player::OnCollisionStay(Collider2D* collider)
	{
	}

	void Player::OnCollisionExit(Collider2D* collider)
	{
	}

}