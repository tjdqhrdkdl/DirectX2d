#include "yaTitleScene.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaCamera.h"
#include "cameraScript.h"
#include "yaObject.h"
#include "yaCollider2D.h"
#include "yaCollisionManager.h"
#include "yaInput.h"
#include "yaLight.h"
#include "yaRigidBody.h"

#include "yaPlayer.h"
#include "yaGroundScript.h"
#include "yaMouseCursor.h"
#include "yaMagicBall.h"
#include "yaMonster.h"
#include "yaBackSky.h"

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
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//{
		//	GameObject* pointLight = object::Instantiate<GameObject>(eLayerType::Player);
		//	pointLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 5.0f));
		//	Light* lightComp = pointLight->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Point);
		//	lightComp->SetRadius(10.0f);
		//	lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		//}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::PlayerProjectTile, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::PlayerProjectTile, true);


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
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
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


		{
			//Player
			Player* player = object::Instantiate<Player>(eLayerType::Player);

			//Ground
			Ground* ground = object::Instantiate<Ground>(eLayerType::Ground);
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0, -5, 0));
			tr->SetScale(Vector3(1, 10, 1));

			//MagicBall
			MagicBall* ball = object::Instantiate<MagicBall>(eLayerType::PlayerProjectTile);
			ball->SetPlayer(player);
			ball->SetType(MagicBullet::eMagicBulletType::XBall);
			//MagicBall2
			MagicBall* ball2 = object::Instantiate<MagicBall>(eLayerType::PlayerProjectTile);
			ball2->SetPlayer(player);
			ball2->SetTheta(XM_2PI / 3);
			ball2->SetType(MagicBullet::eMagicBulletType::YBall);

			//MagicBall3
			MagicBall* ball3 = object::Instantiate<MagicBall>(eLayerType::PlayerProjectTile);
			ball3->SetPlayer(player);
			ball3->SetTheta(XM_2PI *2/ 3);
			ball3->SetType(MagicBullet::eMagicBulletType::ZBall);


			player->SetHeadBall(ball);

			//Cursor
			object::Instantiate<MouseCursor>(eLayerType::UI);

			//monster
			object::Instantiate<Monster>(eLayerType::Monster);

			//BackSky
			object::Instantiate<BackSky>(eLayerType::Ground);


		}



		
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