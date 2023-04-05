#pragma once
#include "yaGameObject.h"
#include "yaMagicBullet.h"

using namespace ya::math;
namespace ya
{
	class MagicBall : public GameObject
	{
	public:
		MagicBall();
		~MagicBall();

		void Initialize() override;
		void Update()override;
		void FixedUpdate()override;
		void Render()override;

		void Revolove();
		void Shoot();
		void Shine();
		void SetPlayer(GameObject* pl) { mOwnerPlayer = pl; }

	private:
		float mTheta;
		Vector3 mPos;
		GameObject* mOwnerPlayer;

		float mBrightness;
		float mMaxBrightness;

		bool mbLightUp;
		MagicBullet::eMagicBulletType mType;
	};
}
