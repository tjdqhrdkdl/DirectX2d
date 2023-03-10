#include "yaGridScript.h"
#include "yaMaterial.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaSceneManager.h"
namespace ya
{
	GridScript::GridScript()
	{
	}

	GridScript::~GridScript()
	{
	}

	void GridScript::Initialize()
	{
	}

	void GridScript::Update()
	{
	}

	void GridScript::FixedUpdate()
	{
		shared_ptr<Material>  material = Resources::Find<Material>(L"GridMaterial");
		eSceneType type = SceneManager::GetPlayScene()->GetSceneType();
		if (material)
		{
			GameObject* camera = renderer::cameras[(UINT)type][1]->GetOwner();
			Transform* tr = camera->GetComponent<Transform>();
			int depth = tr->GetPosition().z;
			
			material->SetData(eGPUParam::Int, &depth);

		}

	}

	void GridScript::Render()
	{
	}

}