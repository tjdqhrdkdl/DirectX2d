#pragma once
#include "yaGameObject.h"

namespace ya 
{
	class Animator;
	class Rigidbody;
	class MagicBall;
	class Player: public GameObject
	{
	public:
		enum ePlayerState
		{
			PlayerState_None = 0x0000,
			PlayerState_LookRight = 0x0001,
			PlayerState_Walk = 0x0002,
			PlayerState_Run = 0x0004,
			PlayerState_Jump = 0x0008,
			PlayerState_Attack = 0x0010,


		};
		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void SetState();
		void SetAnimation();
		void Move();
		void Attack();
		void Jump();

		void Fall();
		void AttackCompleteEvent();

		void SetHeadBall(MagicBall* ball) { mHeadBall = ball; }
	private:

		float mFadeTime;

		Animator* mAnimator;
		Rigidbody* mRigidbody;
		int mState;

		MagicBall* mHeadBall;
		std::vector<MagicBall*> mBalls;
		UINT mHeadNum;

	};
}
