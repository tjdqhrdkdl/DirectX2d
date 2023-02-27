#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSpriteRenderer.h"
#include "yaCamera.h"


namespace ya
{
	using namespace std;

	Scene* SceneManager::mPlayScene = nullptr;
	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		// Main Camera Game Object
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraComp->RegisterCameraInRenderer();
		cameraObj->AddComponent(cameraComp);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		mPlayScene->AddGameObject(cameraObj, eLayerType::Camera);



		GameObject* cameraUIObj = new GameObject();
		Transform* cameraUITr = new Transform();
		cameraUITr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraUIObj->AddComponent(cameraUITr);
		Camera* cameraUIComp = new Camera();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIObj->AddComponent(cameraUIComp);
		mPlayScene->AddGameObject(cameraUIObj, eLayerType::Camera);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		//smile obj
		GameObject* smileObj = new GameObject();
		Transform* smileTr = new Transform();
		smileTr->SetPosition(Vector3(0, 0, 6.0f));
		smileObj->AddComponent(smileTr);
		MeshRenderer* smileMr = new MeshRenderer();
		smileObj->AddComponent(smileMr);
		shared_ptr<Material> smilematerial = Resources::Find<Material>(L"RectMaterial");
		smileMr->SetMaterial(smilematerial);
		smileMr->SetMesh(mesh);

		mPlayScene->AddGameObject(smileObj, eLayerType::Player);

		//Light Object
		GameObject* lightObj = new GameObject();
		Transform* lightTr = new Transform();
		lightTr->SetPosition(Vector3(0.1, 0, 5.0f));
		lightObj->AddComponent(lightTr);

		SpriteRenderer* lightSr = new SpriteRenderer();
		lightObj->AddComponent(lightSr);
		shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		lightSr->SetMaterial(material);
		lightSr->SetMesh(mesh);
		
		mPlayScene->AddGameObject(lightObj, eLayerType::Player);


	

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