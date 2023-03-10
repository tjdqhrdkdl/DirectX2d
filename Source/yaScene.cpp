#include "yaScene.h"

namespace ya
{
	Scene::Scene(eSceneType type)
		:mType(type)
	{
		mLayers.resize((UINT)eLayerType::End);
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (Layer& layer: mLayers )
		{
			layer.Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::OnExit()
	{
	}

	void Scene::OnEnter()
	{
	}

	void Scene::AddGameObject(GameObject* gameobject, enums::eLayerType layerIndex)
	{
		mLayers[(UINT)layerIndex].AddGameObject(gameobject);
	}

}