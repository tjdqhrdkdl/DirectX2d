#pragma once
#include "yaScript.h"

namespace ya
{
	
	class MagicBallScript : public Script
	{
	public:
		MagicBallScript();
		~MagicBallScript();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void SetPlayer(GameObject* player) { mPlayer = player; }
	private:
		float mTheta;
		GameObject* mPlayer;

		Vector3 mPos;
	};
}
