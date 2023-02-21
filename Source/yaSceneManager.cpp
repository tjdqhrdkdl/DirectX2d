#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaCamera.h"


namespace ya
{
	using namespace std;

	Scene* SceneManager::mPlayScene = nullptr;
	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		// Camera Game Object
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraObj->AddComponent(cameraComp);

		mPlayScene->AddGameObject(cameraObj, eLayerType::Camera);

		//smile obj
		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.f, 0.f, 20.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);

		shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		mateiral->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMaterial(mateiral.get());
		mr->SetMesh(mesh.get());

		shared_ptr<Texture> texture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);

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

	void SceneManager::Release()
	{
		delete mPlayScene;
	}

}