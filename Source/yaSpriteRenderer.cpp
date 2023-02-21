#include "yaSpriteRenderer.h"
#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	SpriteRenderer::SpriteRenderer()
		:Component(eComponentType::Mesh)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::FixedUpdate()
	{
	}

	void SpriteRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		mMaterial->Bind();
		mMesh->BindBuffer();
		mMesh->Render();
	}

}