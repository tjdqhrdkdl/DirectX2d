#pragma once
#include "yaScript.h"

namespace ya
{
	class WallScript : public Script
	{
	public:
		WallScript();
		~WallScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* col) ;
		virtual void OnCollisionStay(Collider2D* col) ;
		virtual void OnCollisionExit(Collider2D* col) ;

	};
}
