#pragma once

namespace ya::enums
{
	enum class eLayerType
	{
		None,
		Camera,
		Ground,
		PlayerProjectTile,
		Player,
		Monster,
		UI,
		End,
	};

	enum class eObjectState
	{
		Active,
		Paused,
		Dead,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		MeshRenderer,
		SpriteRenderer,
		Rigidbody,
		Collider,
		//Collider2,
		Animator,
		Light,
		UI,
		Script,
		End,
	};
	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

	enum class eSceneType
	{
		Title,
		Play,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};


	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}