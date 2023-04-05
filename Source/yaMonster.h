#pragma once
#include "yaGameObject.h"


namespace ya
{
	class Monster : public GameObject
	{
	public:
		Monster();
		~Monster();
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* col) {};
		virtual void OnCollisionStay(Collider2D* col) {};
		virtual void OnCollisionExit(Collider2D* col) {};


	private:
	};
}
