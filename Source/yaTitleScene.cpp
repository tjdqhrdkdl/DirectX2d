#include "yaTitleScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSpriteRenderer.h"
#include "yaCamera.h"
#include "cameraScript.h"
#include "yaGridScript.h"
#include "yaCamEffectScript.h"
#include "yaObject.h"
#include "yaCollider2D.h"
#include "yaPlayerScript.h"
#include "yaCollisionManager.h"
#include "yaInput.h"
#include "yaPlayer.h"

namespace ya
{
	TitleScene::TitleScene()
		:Scene(eSceneType::Title)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);

		shared_ptr<Mesh> circleMesh = Resources::Find<Mesh>(L"CircleMesh");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		// Grid Camera Game Object

		GameObject* gridCameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* gridCameraComp = gridCameraObj->AddComponent<Camera>();
		gridCameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		gridCameraComp->DisableLayerMasks();
		gridCameraComp->TurnLayerMask(eLayerType::None, true);
		renderer::orthographicCamera = gridCameraComp;

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();	
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraComp->TurnLayerMask(eLayerType::None, false);
		cameraScript* camScript = cameraObj->AddComponent<cameraScript>();
		renderer::mainCamera = cameraComp;


		//UI Camer Game Object
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);



		//smile obj
		object::Instantiate<Player>(eLayerType::Player);



		// HPBAR
		GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI);
		hpBar->SetName(L"HPBAR");
		Transform* hpBarTR = hpBar->GetComponent<Transform>();
		hpBarTR->SetPosition(Vector3(-0.5, 3.0f, 12.0f));
		hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		hpsr->SetMesh(mesh);
		hpsr->SetMaterial(hpspriteMaterial);

		//// Camera Effect
		//GameObject* camEffect = object::Instantiate<GameObject>(eLayerType::UI);
		//camEffect->SetName(L"CameraEffect");
		//Transform* camEffectTR = camEffect->GetComponent<Transform>();
		//camEffectTR->SetPosition(Vector3(0.0f, 0.0f, 0.0f));5
		//SpriteRenderer* camEffectsr = camEffect->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Mesh> camEffectmesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> camEffectspriteMaterial = Resources::Find<Material>(L"CamEffectMaterial");
		//camEffectsr->SetMesh(circleMesh);
		//camEffectsr->SetMaterial(camEffectspriteMaterial);
		//CamEffectScript* ceScript = camEffect->AddComponent<CamEffectScript>();

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
			SceneManager::LoadScene(eSceneType::Play);
		Scene::Update();
	}

	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}

	void TitleScene::OnEnter()
	{
	}

	void TitleScene::OnExit()
	{
	}

}