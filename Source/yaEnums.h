#pragma once

namespace ya::enums
{
	enum class eLayerType
	{
		None,
		Camera,
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
		Collider,
		//Collider2,
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
}