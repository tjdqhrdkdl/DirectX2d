#pragma once
#include "yaComponent.h"
#include "yaTransform.h"

namespace ya
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }
		void SetRadius(float radius) { mRadius = radius; }
		void SetJumpBox(bool isJumpBox) { mbJumpBox = isJumpBox; }
		bool IsTriiger() { return mbTrigger; }

		float GetRadius() { return mRadius; }
		UINT GetID() { return mID; }
		eColliderType GetColliderType() { return mType; }
		Vector3 GetPosition() { return mPosition; }
		Vector2 GetSize() { return mSize; }
		Vector3 GetScale() { return mScale; }
		bool isJumpBox() { return mbJumpBox; }
		bool isOn() { return mbOn; }
		void SetOn(bool on) { mbOn = on; }
	private:
		static UINT ColliderNumber;
		UINT mID;
		eColliderType mType;
		Transform* mTransform;

		Vector2 mSize;
		Vector2 mCenter;
		Vector3 mPosition;
		Vector3 mScale;
		float mRadius;
		bool mbTrigger;
		bool mbJumpBox;

		bool mbOn;
	};
}
