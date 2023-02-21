#pragma once

namespace ya::enums
{
	enum class eLayerType
	{
		None,
		Camera,
		Player,
		Monster,
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
		Transform, // ��ġ ������ �����ϴ� ������Ʈ
		Camera,
		Mesh,
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