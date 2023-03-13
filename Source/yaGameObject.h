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
		T* AddComponent()
		{
			T* comp = new T();
			AddComponent(comp);
			return comp;

		}

		template <typename T>
		std::vector<T*> GetComponents()
		{
			T comp = {};
			std::vector<T*> ret = {};
			for (Component* c:mvComponents[comp.GetOrder()])
			{
				ret.push_back(dynamic_cast<T*>(c));
			}
			return ret;
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

		eState GetState() { return mState; }
	protected:
		std::vector<std::vector<Component*>> mvComponents;
	private:
		eState mState;
	};
}
