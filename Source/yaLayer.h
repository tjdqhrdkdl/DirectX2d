#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Layer
	{
	public:
		Layer();
		~Layer();
		void Initialize();
		void Update();
		void FixedUpdate();
		void Render();
		
		void AddGameObject(GameObject* gameobject);
	private:
		std::vector<GameObject*> mObjects;
	};
}
