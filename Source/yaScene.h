#pragma once
#include "yaLayer.h"

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

		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

		eSceneType GetSceneType() { return mType; }
	private:
		std::vector<Layer> mLayers;
		eSceneType mType;
	};
}
