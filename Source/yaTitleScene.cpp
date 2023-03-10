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
		shared_ptr<Mesh> circleMesh = Resources::Find<Mesh>(L"CircleMesh");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		// Grid Camera Game Object

		GameObject* gridCameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* gridCameraComp = gridCameraObj->AddComponent<Camera>();
		gridCameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		gridCameraComp->DisableLayerMasks();
		gridCameraComp->TurnLayerMask(eLayerType::None, true);

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();	
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraComp->TurnLayerMask(eLayerType::None, false);
		cameraScript* camScript = cameraObj->AddComponent<cameraScript>();


		//UI Camer Game Object
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);


		//grid Object
		GameObject* gridObj = object::Instantiate<GameObject>(eLayerType::None);
		gridObj->SetName(L"Grid");
		Transform* gridTr = gridObj->GetComponent<Transform>();
		gridTr->SetPosition(Vector3(0.0f, .4f, 999.0f));
		gridTr->SetScale(Vector3(20.0f, 10.0f, 0));
		GridScript* gscript = gridObj->AddComponent<GridScript>();
		SpriteRenderer* gridSr = gridObj->AddComponent<SpriteRenderer>();
		shared_ptr<Material> gridMaterial = Resources::Find<Material>(L"GridMaterial");
		gridSr->SetMesh(mesh);
		gridSr->SetMaterial(gridMaterial);

		//smile obj
		GameObject* smileObj = object::Instantiate<GameObject>(eLayerType::Player);
		Transform* smileTr = smileObj->GetComponent<Transform>();
		smileTr->SetPosition(Vector3(3, 2, 5));
		smileTr->SetRotation(Vector3(0.0f, 0.0f, 0));
		MeshRenderer* smileMr = smileObj->AddComponent<MeshRenderer>();
		shared_ptr<Material> smilematerial = Resources::Find<Material>(L"RectMaterial");
		smileMr->SetMaterial(smilematerial);
		smileMr->SetMesh(circleMesh);

		//smile Child obj
		GameObject* childObj = object::Instantiate<GameObject>(eLayerType::Player);
		Transform* childTr = childObj->GetComponent<Transform>();
		childTr->SetPosition(Vector3(3, 0, 5));
		childTr->SetParent(smileTr);
		MeshRenderer* childMr = childObj->AddComponent<MeshRenderer>();
		shared_ptr<Material> childmaterial = Resources::Find<Material>(L"RectMaterial");
		childMr->SetMaterial(childmaterial);
		childMr->SetMesh(circleMesh);

		//Light Object
		GameObject* lightObj = object::Instantiate<GameObject>(eLayerType::Player);
		Transform* lightTr = lightObj->GetComponent<Transform>();
		lightTr->SetPosition(Vector3(0.1, 0, 5.0f));

		SpriteRenderer* lightSr = lightObj->AddComponent<SpriteRenderer>();
		shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		lightSr->SetMaterial(material);
		lightSr->SetMesh(circleMesh);

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

		// Camera Effect
		GameObject* camEffect = object::Instantiate<GameObject>(eLayerType::UI);
		camEffect->SetName(L"CameraEffect");
		Transform* camEffectTR = camEffect->GetComponent<Transform>();
		camEffectTR->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		SpriteRenderer* camEffectsr = camEffect->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> camEffectmesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> camEffectspriteMaterial = Resources::Find<Material>(L"CamEffectMaterial");
		camEffectsr->SetMesh(circleMesh);
		camEffectsr->SetMaterial(camEffectspriteMaterial);
		CamEffectScript* ceScript = camEffect->AddComponent<CamEffectScript>();

		Scene::Initialize();
	}

	void TitleScene::Update()
	{

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