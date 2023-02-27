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
			for (std::vector<Component*> componentVector : mvComponents)
			{
				for (Component* comp : componentVector)
				{
					T* ret = dynamic_cast<T*>(comp);
					if (ret != nullptr)
						return ret;
				}
			}
			return nullptr;
		}

	private:
		eState mState;
		std::vector<std::vector<Component*>> mvComponents;
	};
}
