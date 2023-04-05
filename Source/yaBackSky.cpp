#include "yaBackSky.h"
#include "yaTransform.h"
#include "yaSpriteRenderer.h"

//manager
#include "yaResources.h"
namespace ya
{
	BackSky::BackSky()
	{
	}

	BackSky::~BackSky()
	{
	}

	void BackSky::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(40, 40, 1));
		tr->SetPosition(Vector3(0, 0, 100));

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		shared_ptr<Material> material = Resources::Find<Material>(L"SkyMaterial");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);

	}

	void BackSky::Update()
	{
		GameObject::Update();
	}

	void BackSky::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void BackSky::Render()
	{
		GameObject::Render();
	}

}