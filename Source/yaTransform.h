#pragma once
#include "yaComponent.h"

using namespace ya::math;
namespace ya
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

		Vector3 GetPosition() { return mPosition; };
		Vector3 GetRotation() { return mRotation; };
		Vector3 GetScale() { return mScale; };

		Vector3 Forward() { return mForward; }
		Vector3 Up() { return mUp; }
		Vector3 Right() { return mRight; }

		void SetPosition(Vector3 position) { mPosition = position; };
		void SetRotation(Vector3 rotation) { mRotation = rotation; };
		void SetScale(Vector3 scale) { mScale = scale; };

		void SetParent(Transform* tr) { mParent = tr; }
		Transform* GetParent() { return mParent; }
	private:
		Vector3 mForward;
		Vector3 mUp;
		Vector3 mRight;

		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Matrix mWorldMatrix;
		Transform* mParent;
	};
}
