#include "yaGameObject.h"


namespace ya
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		mvComponents.resize((UINT)eComponentType::End);
	}

	GameObject::~GameObject()
	{
		for (std::vector<Component*> mComponents : mvComponents)
		{
			for (Component* comp : mComponents)
			{
				if (comp == nullptr)
					continue;

				delete comp;
			}
		}
	}

	void GameObject::Initialize()
	{
		for (std::vector<Component*> mComponents : mvComponents)
		{
			for (Component* comp : mComponents)
			{
				if (comp == nullptr)
					continue;

				comp->Initialize();
			}
		}
	}

	void GameObject::Update()
	{
		for (std::vector<Component*> mComponents : mvComponents)
		{
			for (Component* comp : mComponents)
			{
				if (comp == nullptr)
					continue;

				comp->Update();
			}
		}
	}

	void GameObject::FixedUpdate()
	{
		for (std::vector<Component*> mComponents : mvComponents)
		{
			for (Component* comp : mComponents)
			{
				if (comp == nullptr)
					continue;

				comp->FixedUpdate();
			}
		}
	}

	void GameObject::Render()
	{
		for (std::vector<Component*> mComponents : mvComponents)
		{
			for (Component* comp : mComponents)
			{
				if (comp == nullptr)
					continue;

				comp->Render();
			}
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
		int order = comp->GetOrder();
		mvComponents[order].push_back(comp);
		
		comp->SetOwner(this);
	}


}
