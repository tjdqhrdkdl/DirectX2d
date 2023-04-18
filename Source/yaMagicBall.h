#pragma once
#include "yaGameObject.h"
#include "yaMagicBullet.h"

using namespace ya::math;
namespace ya
{
	class Player;
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
		bool Shoot();
		void Shine();
		void Activate();
		void SetPlayer(Player* pl);

		void SetType(MagicBullet::eMagicBulletType type) { mType = type; }
		void SetTheta(float theta) { mTheta = theta; }
		void SetHead(bool head) { mbHead = head; }
	private:
		Vector3 mPos;
		MagicBullet::eMagicBulletType mType;
		Player* mOwnerPlayer;

		float mTheta;
		float mBrightness;
		float mMaxBrightness;
		float mActiveTimeChecker;

		bool mbLightUp;
		bool mbHead;
		bool mbActive;

	};
}
