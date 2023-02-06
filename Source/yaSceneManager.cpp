#include "yaSceneManager.h"
#include "yaRenderer.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"


namespace ya
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();
		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.2f, 0.2f, 0.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		mr->SetShader(renderer::shader);
		mr->SetMesh(renderer::mesh);


		mPlayScene->AddGameObject(obj, eLayerType::Player);
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

}