#pragma once
#include "yaComponent.h"
#include "yaMesh.h"
#include "yaShader.h"

using namespace ya::graphics;
namespace ya
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetShader(Shader* shader) { mShader = shader; }

	private:
		Mesh* mMesh;
		Shader* mShader;
	};
}