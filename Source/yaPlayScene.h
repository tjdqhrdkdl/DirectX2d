#pragma once
#include "yaScene.h"


namespace ya
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();
		virtual void Initialize() override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

	private:

	};
}
