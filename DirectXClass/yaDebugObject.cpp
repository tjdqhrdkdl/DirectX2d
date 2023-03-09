#include "yaDebugObject.h"


namespace ya
{
	DebugObject::DebugObject()
	{

	}
	DebugObject::~DebugObject()
	{

	}

	void DebugObject::FixedUpdate()
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
}