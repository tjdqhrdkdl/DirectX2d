#include "yaSceneManager.h"
#include "yaTitleScene.h"
#include "yaPlayScene.h"
namespace ya
{
	using namespace std;

	Scene* SceneManager::mPlayScene = nullptr;
	std::vector<Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{

		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();

		for (Scene* scene:mScenes)
		{
			mPlayScene = scene;
			scene->Initialize();
		}

		mPlayScene = mScenes[(UINT)eSceneType::Title];


	}

	void SceneManager::Update()
	{
		mPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene->Render();
	}

	void SceneManager::Release()
	{
		delete mPlayScene;
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		mPlayScene->OnExit();
		mPlayScene = mScenes[(UINT)type];
		mPlayScene->OnEnter();
	}

}