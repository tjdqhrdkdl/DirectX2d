#pragma once
#include "yaLayer.h"

using namespace ya::math;
namespace ya
{
	class Scene
	{
	public:
		Scene(eSceneType type);
		virtual ~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	
		virtual void OnExit();
		virtual void OnEnter();

		void AddGameObject(GameObject* gameobject, enums::eLayerType layerIndex);

		std::vector<GameObject*> GetGameObjects(eLayerType type) { return mLayers[(UINT)type].GetGameObjects(); }
		std::vector<GameObject*>* GetGameObjectsPtr(eLayerType type) { return mLayers[(UINT)type].GetGameObjectsPtr(); }

		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }
		eSceneType GetSceneType() { return mType; }

		void SetMousePos(Vector2 pos) { mMousePos = pos; }
		Vector2 GetMousePos() { return mMousePos; }

	private:
		std::vector<Layer> mLayers;
		eSceneType mType;
		Vector2 mMousePos;
	};
}
