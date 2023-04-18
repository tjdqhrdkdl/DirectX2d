#include "yaGameObject.h"
#include "yaTransform.h"

#include "yaTime.h"
namespace ya
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mSize(1.0f)
		, mMinSize(0.3f)
		, mMaxSize(2)
		, mbTransed(false)
		, mTransTime(5.0f)
		, mTransTimeChecker(0)
		, mBaseScale(Vector3(1,1,1))
	{
		mvComponents.resize((UINT)eComponentType::End);
		AddComponent(new Transform());
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
		Restore();
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

	void GameObject::Restore()
	{
		if (mbTransed)
		{
			mTransTimeChecker += Time::DeltaTime();
			if (mTransTimeChecker > mTransTime)
			{
				mTransTimeChecker = 0;
				SetSize(1.0f);
				mbTransed = false;
			}
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
		int order = comp->GetOrder();
		mvComponents[order].push_back(comp);
		
		comp->SetOwner(this);
	}

	void GameObject::SetSize(float size)
	{
		if (size > mMaxSize)
			size = mMaxSize;
		if (size < mMinSize)
			size = mMinSize;

		mSize = size;
		mbTransed = true;
		mTransTimeChecker = 0;
		GetComponent<Transform>()->SetScale(mBaseScale * mSize);

	}


}
