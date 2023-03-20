#pragma once
#include "yaGameObject.h"

namespace ya 
{
	class Animator;
	class Player:public GameObject
	{
		friend class PlayerScript;
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

		void SetState();
		void SetAnimation();
		void Move();
	
	private:
		float mHp;
		float mSpeed;
		float mDamage;
		float mSize;

		float mFadeTime;

		Animator* mAnimator;
		int mState;
	};
}
