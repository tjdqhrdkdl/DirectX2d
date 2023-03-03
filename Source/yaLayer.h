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

		std::vector<GameObject*> GetGameObjects() { return mObjects; }
	private:
		std::vector<GameObject*> mObjects;
	};
}
