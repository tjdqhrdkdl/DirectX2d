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
		smileTr->SetPosition(Vector3(3, 2, 5));
		smileTr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));

		smileObj->AddComponent(smileTr);
		MeshRenderer* smileMr = new MeshRenderer();
		smileObj->AddComponent(smileMr);
		shared_ptr<Material> smilematerial = Resources::Find<Material>(L"RectMaterial");
		smileMr->SetMaterial(smilematerial);
		smileMr->SetMesh(mesh);

		mPlayScene->AddGameObject(smileObj, eLayerType::Player);

		//smile Child obj
		GameObject* childObj = new GameObject();
		Transform* childTr = new Transform();
		childTr->SetPosition(Vector3(3, 0, 5));
		childObj->AddComponent(childTr);
		MeshRenderer* childMr = new MeshRenderer();
		childObj->AddComponent(childMr);
		shared_ptr<Material> childmaterial = Resources::Find<Material>(L"RectMaterial");
		childMr->SetMaterial(childmaterial);
		childMr->SetMesh(mesh);
		childTr->SetParent(smileTr);
		mPlayScene->AddGameObject(childObj, eLayerType::Player);

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

		// HPBAR
		GameObject* hpBar = new GameObject();
		hpBar->SetName(L"HPBAR");
		Transform* hpBarTR = new Transform();
		hpBarTR->SetPosition(Vector3(-0.5, 3.0f, 12.0f));
		hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		hpBar->AddComponent(hpBarTR);

		SpriteRenderer* hpsr = new SpriteRenderer();
		hpBar->AddComponent(hpsr);

		std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		//.std::shared_ptr <Texture> hpTexture = Resources::Find<Texture>(L"HPBarTexture");
		//spriteMaterial->SetTexture(hpTexture);

		hpsr->SetMesh(hpmesh);
		hpsr->SetMaterial(hpspriteMaterial);
		mPlayScene->AddGameObject(hpBar, eLayerType::UI);


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