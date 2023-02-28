#pragma once
#include "yaScript.h"

namespace ya
{
	class CamEffectScript : public Script
	{
	public:
		CamEffectScript();
		~CamEffectScript();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		float mFadeTime;
	};
}
