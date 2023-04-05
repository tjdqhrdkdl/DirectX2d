#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MagicBullet : public GameObject
	{
	public:
		enum class eMagicBulletType
		{
			None,
			Red,
			Blue,
		};

		MagicBullet();
		~MagicBullet();

		void Initialize() override;
		void Update()override;
		void FixedUpdate()override;
		void Render()override;

		virtual void OnCollisionEnter(Collider2D* col);
		virtual void OnCollisionStay(Collider2D* col) ;
		virtual void OnCollisionExit(Collider2D* col) ;

		void SetDir(Vector3 dir) { mDir = dir; }

	private:
		float mSpeed;
		Vector3 mDir;

		float mAliveTime;
		float mAliveTimeChecker;

	};
}
