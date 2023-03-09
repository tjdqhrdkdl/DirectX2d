#pragma once
#include "..\Source\yaGameObject.h"


namespace ya
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;

	private:
	};
}
