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

	private:

	};
}
