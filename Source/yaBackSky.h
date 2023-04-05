#pragma once
#include "yaGameObject.h"

namespace ya
{
	class BackSky:public GameObject
	{
	public:
		BackSky();
		~BackSky();
		void Initialize() override;
		void Update()override;
		void FixedUpdate()override;
		void Render()override;

	private:

	};
}
