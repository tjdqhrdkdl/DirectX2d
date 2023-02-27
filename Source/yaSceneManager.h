#pragma once
#include "yaScene.h"

namespace ya
{
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();

		static void Release();

		static Scene* GetPlayScene() { return mPlayScene; }

	private:
		static Scene* mPlayScene;
	};
}
