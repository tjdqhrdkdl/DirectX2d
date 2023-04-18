#pragma once
#include "yaScene.h"
#include "yaLayer.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaTransform.h"

namespace ya::object
{
	template <typename T>
	static T* Instantiate(enums::eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetPlayScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);
		gameObj->SetLayerType(type);
		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Scene* scene)
	{
		T* gameObj = new T();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);
		gameObj->SetLayerType(type);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetPlayScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetParent(parent);
		gameObj->SetLayerType(type);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetPlayScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);
		gameObj->SetLayerType(type);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetPlayScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);
		tr->SetParent(parent);
		gameObj->SetLayerType(type);

		return gameObj;
	}

	static __forceinline void Release()
	{
		Scene* scene = SceneManager::GetPlayScene();
		for (size_t y = 0; y < (UINT)eLayerType::End; y++)
		{
			std::vector<GameObject*>* objs = scene->GetGameObjectsPtr((eLayerType)y);
			for (std::vector<GameObject*>::iterator iter = objs->begin()
				; iter !=objs->end();)
			{
				if ((*iter)->isDead() == true)
				{
					GameObject* obj = *iter;
					iter = objs->erase(iter);
					delete obj;
					obj = nullptr;
					continue;
				}
				++iter;
			}
		}
	}

}