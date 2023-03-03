#pragma once
#include "yaScene.h"


namespace ya
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();
		virtual void Initialize() override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

	private:

	};
}
