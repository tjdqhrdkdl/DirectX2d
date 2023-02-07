#include "yaLayer.h"


namespace  ya
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mObjects)
		{
			if (obj != nullptr)
				delete obj;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* obj:mObjects)
		{
			if(obj != nullptr)
				obj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mObjects)
		{
			if (obj != nullptr)
				obj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* obj : mObjects)
		{
			if (obj != nullptr)
				obj->FixedUpdate();
		}
	}

	void Layer::Render()
	{
		for (GameObject* obj : mObjects)
		{
			if (obj != nullptr)
				obj->Render();
		}
	}

	void Layer::AddGameObject(GameObject* gameobject)
	{
		if (gameobject == nullptr)
			return;

		mObjects.push_back(gameobject);
	}

}