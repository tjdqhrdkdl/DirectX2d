#pragma once
#include "yaScript.h"

namespace ya
{
	class GridScript : public Script
	{
	public:
		GridScript();
		~GridScript();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}
