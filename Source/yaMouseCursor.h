#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MouseCursor : public GameObject
	{
	public:
		MouseCursor();
		~MouseCursor();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* col) {};
		virtual void OnCollisionStay(Collider2D* col) {};
		virtual void OnCollisionExit(Collider2D* col) {};

	};
}
