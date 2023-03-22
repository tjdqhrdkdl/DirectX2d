#pragma once
#include "CommonInclude.h"
#include "yaMath.h"
#include "yaGraphicDevice_DX11.h"

#include "yaMesh.h"
#include "yaShader.h"
#include "yaConstantBuffer.h"
#include "yaStructuredBuffer.h"
#include "yaCamera.h"
using namespace ya::math;
using namespace ya::graphics;


namespace	ya::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 vector2;
		Vector3 vector3;
		Vector4 vector4;
		Matrix matrix;

	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATOR)
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 offset;
		bool reversed;

		UINT type;
	};

	CBUFFER(LightCB, CBSLOT_ANIMATOR)
	{
		UINT numberOfLight;
	};

	extern Vertex vertexes[4];
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];

	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<ya::Camera*> cameras[];
	extern Camera* mainCamera;
	extern Camera* orthographicCamera;
	extern std::vector<DebugMesh> debugMeshes;
	extern std::vector<LightAttribute> lights;
	extern StructuredBuffer* lightsBuffer;

	void Initialize();
	void Render();
	void Release();
	void PushLightAttribute(LightAttribute lightAttribute);
	void BindLights();


}
