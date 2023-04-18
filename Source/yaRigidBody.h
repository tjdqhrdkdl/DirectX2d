#pragma once
#include "yaComponent.h"

using namespace ya::math;
namespace ya
{
	class Rigidbody : public Component
	{
		public:
			Rigidbody();
			~Rigidbody();

			virtual void Initialize() override;
			virtual void Update() override;
			virtual void FixedUpdate() override;
			virtual void Render() override;
			void AddForce(Vector3 force) { mForce += force; }
			void SetMass(float mass) { mMass = mass; }
			void SetGround(bool isGround) { mbGround = isGround; }
			bool isGround() { return mbGround; }
			bool isFalling() { return mVelocity.y < 0; }
			Vector3 GetVelocity() { return mVelocity; }
			void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
			void SetGravity(Vector3 gravity) { mGravity = gravity; }

			void PushX(float x) { mForce.x += x; mbPushed = true; }
			void PushY(float y) { mForce.y += y; mbPushed = true; }

		private:
			// 힘과 마찰력을 이용한 이동
			float mMass;
			float mFriction;

			//float mMoveFriction;
			Vector3 mForce;
			Vector3 mVelocity;
			Vector3 mAccelation;

			// 중력 이용한 점프
			Vector3 mGravity;
			bool mbPushed;
			bool mbGround;
			Vector3 mLimitVelocity;

	};
}
