#pragma once
#include "yaEntity.h"
#include "yaComponent.h"


namespace ya
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddComponent(Component* comp);

		template <typename T>
		std::vector<Component*> GetComponents()
		{
			T comp = {};
			return mvComponents[comp.GetOrder()];
		}

		template <typename T>
		T* GetComponent()
		{
			T comp = {};
			if (mvComponents[comp.GetOrder()].size() > 0)
				return dynamic_cast<T*>(mvComponents[comp.GetOrder()][0]);
			return nullptr;
		}

	private:
		eState mState;
		std::vector<std::vector<Component*>> mvComponents;
	};
}
