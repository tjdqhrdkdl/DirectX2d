#pragma once
#include "yaScript.h"
namespace ya
{
	class GroundScript: public Script
	{
	public:
		GroundScript();
		~GroundScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	};
}
