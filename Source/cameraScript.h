#pragma once
#include "yaScript.h"

namespace ya
{
	class cameraScript: public Script
	{
	public:
		cameraScript();
		~cameraScript();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}
