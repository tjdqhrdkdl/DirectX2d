#include "yaMouseCursor.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"
#include "yaAnimator.h"
#include "yaLight.h"

/*Managers*/
#include "yaResources.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaSceneManager.h"
namespace ya
{
	MouseCursor::MouseCursor()
	{
	}

	MouseCursor::~MouseCursor()
	{
	}

	void MouseCursor::Initialize()
	{

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(1.0, 1.0, 1));

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"CircleMesh");
		shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);

		Animator* animator = AddComponent<Animator>();
		shared_ptr<Texture> atlas = Resources::Load<Texture>(L"aimCursor", L"AimCursor//Aim.png");

		animator->Create(L"Idle", atlas, Vector2(0, 0), Vector2(100, 100), Vector2::Zero, 1, 0.3f);

		animator->Play(L"Idle", false);
		GameObject::Initialize();
	}

	void MouseCursor::Update()
	{
		Vector2 mousePos = Input::GetMousePosition();
		Vector4 pos = Vector4(mousePos.x / 800 - 1, 1 - mousePos.y / 450, 1, 1);
		pos = Vector4::Transform(pos, renderer::mainCamera->GetProjectionMatrix().Invert());
		pos= Vector4::Transform(pos, renderer::mainCamera->GetViewMatrix().Invert());
		GetComponent<Transform>()->SetPosition(Vector3(pos.x,pos.y,1));
		SceneManager::GetPlayScene()->SetMousePos(Vector2(pos.x, pos.y));

		GameObject::Update();

	}

	void MouseCursor::FixedUpdate()
	{
		GameObject::FixedUpdate();

	}

	void MouseCursor::Render()
	{
		GameObject::Render();

	}

}