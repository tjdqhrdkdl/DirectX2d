#pragma once
#include "..\Source\yaGameObject.h"


namespace ya
{
	class EditorObject : public GameObject
	{
	public:
		enum eProjectionType
		{
			Perspective = 0,
			Orthographic = 1,
		};
		EditorObject();
		virtual ~EditorObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetProjectionType(eProjectionType type) { mType = type; }
		eProjectionType GetProjectionType() { return mType; }
	private:
		eProjectionType mType;
	};
}