#include "yaSceneManager.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSpriteRenderer.h"
#include "yaCamera.h"
#include "cameraScript.h"
#include "yaGridScript.h"
namespace ya
{
	using namespace std;

	Scene* SceneManager::mPlayScene = nullptr;
	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");



		// Grid Camera Game Object
		GameObject* gridCameraObj = new GameObject();
		Transform* gridCameraTr = new Transform();
		gridCameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		gridCameraObj->AddComponent(gridCameraTr);
		Camera* gridCameraComp = new Camera();
		gridCameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		gridCameraObj->AddComponent(gridCameraComp);
		gridCameraComp->DisableLayerMasks();
		gridCameraComp->TurnLayerMask(eLayerType::None, true);

		mPlayScene->AddGameObject(gridCameraObj, eLayerType::Camera);

		// Main Camera Game Object
		GameObject* cameraObj = new GameObject();
		Transform* cameraTr = new Transform();
		cameraTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		cameraObj->AddComponent(cameraTr);
		Camera* cameraComp = new Camera();
		cameraObj->AddComponent(cameraComp);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraComp->TurnLayerMask(eLayerType::None, false);
		cameraScript* camScript = new cameraScript();
		cameraObj->AddComponent(camScript);

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


		//grid Object
		GameObject* gridObj = new GameObject();
		gridObj->SetName(L"Grid");
		Transform* gridTr = new Transform();
		gridTr->SetPosition(Vector3(0.0f, 0.0f, 999.0f));
		gridTr->SetScale(Vector3(20.0f, 10.0f, 0));
		GridScript* gscript = new GridScript();
		gridObj->AddComponent(gscript);
		SpriteRenderer* gridSr = new SpriteRenderer();
		shared_ptr<Material> gridMaterial = Resources::Find<Material>(L"GridMaterial");

		gridSr->SetMesh(mesh);
		gridSr->SetMaterial(gridMaterial);

		gridObj->AddComponent(gridTr);
		gridObj->AddComponent(gridSr);

		mPlayScene->AddGameObject(gridObj, eLayerType::None);

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

		//Fade In Out
		GameObject* CamEffect

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