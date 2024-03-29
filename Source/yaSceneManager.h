#pragma once
#include "yaScene.h"

namespace ya
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();

		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetPlayScene() { return mPlayScene; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mPlayScene;
	};
}
