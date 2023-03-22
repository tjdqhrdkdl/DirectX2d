#pragma once
#include "yaScript.h"

namespace ya 
{
	class Animator;
	class Rigidbody;
	class PlayerScript: public Script
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
		PlayerScript();
		~PlayerScript();

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
	
	private:
		float mHp;
		float mSpeed;
		float mDamage;
		float mSize;

		float mFadeTime;

		Animator* mAnimator;
		Rigidbody* mRigidbody;
		int mState;
	};
}
