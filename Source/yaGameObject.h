#pragma once
#include "yaEntity.h"
#include "yaComponent.h"

using namespace ya::math;
namespace ya
{
	class Collider2D;
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

		void Restore();

		eState GetState() { return mState; }
		eLayerType GetLayerType() { return mLayerType; }
		void SetDead() { mState = eState::Dead; }
		bool isDead() { return mState == eState::Dead; }

		void SetSize(float size);
		float GetSize() { return mSize; }

		virtual void OnCollisionEnter(Collider2D* col) {};
		virtual void OnCollisionStay(Collider2D* col) {};
		virtual void OnCollisionExit(Collider2D* col) {};


		virtual void OnTriggerEnter(Collider2D* col) {};
		virtual void OnTriggerStay(Collider2D* col) {};
		virtual void OnTriggerExit(Collider2D* col) {};
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

	protected:
		std::vector<std::vector<Component*>> mvComponents;
		float mHp;
		float mSize;
		float mDamage;
		float mSpeed;

		float mMinSize;
		float mMaxSize;
		float mTransTime;
		float mTransTimeChecker;
		bool mbTransed;
		
		Vector3 mBaseScale;

		
	private:
		eState mState;
		eLayerType mLayerType;
	};
}
