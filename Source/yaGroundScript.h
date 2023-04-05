#pragma once
#include "yaGameObject.h"
namespace ya
{
	class Ground: public GameObject
	{
	public:
		Ground();
		~Ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	};
}
