#pragma once
#include "yaLayer.h"

namespace ya
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		void Initialize();
		void Update();
		void FixedUpdate();
		void Render();
	
		void AddGameObject(GameObject* gameobject, enums::eLayerType layerIndex);
	private:
		std::vector<Layer> mLayers;
	};
}
