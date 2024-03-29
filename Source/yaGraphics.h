#pragma once

#include <wrl.h>
#include "yaMath.h"
#include "yaEnums.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0
#define CBSLOT_MATERIAL 1
#define CBSLOT_ANIMATOR 2
#define CBSLOT_Light 3

namespace ya::graphics
{
	enum class ValidationMode
	{
		Disabled,
		Enabled,
		GPU,
	};

	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		Count,
	};

	enum class eCBType
	{
		Transform,
		Material,
		Animator,
		Light,
		End,
	};

	enum class eSamplerType
	{
		Point,
		Linear,
		Anisotropic,
		End
	};

	enum class eRSType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		End,
	};

	enum class eDSType
	{
		Less,
		Greater,
		NoWrite,
		None,
		End,
	};

	enum class eBSType
	{
		Default,
		AlphaBlend,
		OneOne,
		End,
	};
	enum class eSRVType
	{
		None,
		End,
	};
	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		End,
	};

	struct GpuBuffer
	{
		enum class eType
		{
			Buffer,
			Texture,
			UnknownType,
		} type = eType::UnknownType;

		D3D11_BUFFER_DESC desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};
	
	enum class eGPUParam
	{
		Int,
		Float,
		Vector2	,
		Vector3,
		Vector4,
		Matrix,
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotatation;
		math::Vector3 scale;
		float radius;
		float duration;
		float time;
	};

	struct LightAttribute
	{
		math::Vector4 diffuse;
		math::Vector4 specular;
		math::Vector4 ambient;
		math::Vector4 position;
		math::Vector4 direction;

		enums::eLightType type;
		float radius;
		float angle;
		int padding;
	};
}