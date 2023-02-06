#pragma once
#include "CommonInclude.h"
#include "yaMath.h"
#include "yaGraphicDevice_DX11.h"

#include "yaMesh.h"
#include "yaShader.h"
#include "yaConstantBuffer.h"
using namespace ya::math;
using namespace ya::graphics;


namespace	ya::renderer
{

	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};


	extern Vertex vertexes[4];
	extern ConstantBuffer* constantBuffers[];
	extern Mesh* mesh;
	extern Shader* shader;

	void Initialize();
	void Release();

}
