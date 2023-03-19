#pragma once
#include "yaGameObject.h"

namespace ya 
{
	class Player:public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	
	private:
	};
}
