#pragma once
#include "yaComponent.h"
#include "yaCollider2D.h"

namespace ya
{
	class Script: public Component
	{
	public:
		Script();
		~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* col) {};
		virtual void OnCollisionStay(Collider2D* col) {};
		virtual void OnCollisionExit(Collider2D* col) {};


		virtual void OnTriggerEnter(Collider2D* col) {};
		virtual void OnTriggerStay(Collider2D* col) {};
		virtual void OnTriggerExit(Collider2D* col) {};
	private:

	};
}
