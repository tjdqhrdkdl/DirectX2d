#include "yaEditor.h"
#include "Source/yaMesh.h"
#include "Source/yaResources.h"
#include "Source/yaMaterial.h"
#include "Source/yaTransform.h"
#include "Source/yaMeshRenderer.h"
#include "Source/yaGridScript.h"
#include "Source/yaObject.h"

namespace ya
{
	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"DebugRectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		MeshRenderer* renderer
			= mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();

		renderer->SetMaterial(material);
		renderer->SetMesh(rectMesh);

		std::shared_ptr<Mesh> circleMesh = Resources::Find<Mesh>(L"DebugCircleMesh");

		mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
		renderer
			= mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();

		renderer->SetMaterial(material);
		renderer->SetMesh(circleMesh);

		// Grid Object
		EditorObject* gridObject = new EditorObject();
		gridObject->SetProjectionType(EditorObject::eProjectionType::Orthographic);
		MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
		gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		GridScript* gridScript = gridObject->AddComponent<GridScript>();

		Transform* gridTr = gridObject->GetComponent<Transform>();
		gridTr->SetPosition(Vector3(0.0f, .4f, 999.0f));
		gridTr->SetScale(Vector3(20.0f, 10.0f, 0));
		mEditorObjects.push_back(gridObject);

	}

	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::FixedUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->FixedUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			if (obj->GetProjectionType() == EditorObject::eProjectionType::Perspective)
			{
				Camera::SetGpuViewMatrix(renderer::mainCamera->GetViewMatrix());
				Camera::SetGpuProjectionMatrix(renderer::mainCamera->GetProjectionMatrix());
			}
			else
			{
				Camera::SetGpuViewMatrix(renderer::orthographicCamera->GetViewMatrix());
				Camera::SetGpuProjectionMatrix(renderer::orthographicCamera->GetProjectionMatrix());
			}
			obj->Render();
		}

		for (DebugMesh& mesh : renderer::debugMeshes)
		{
			DebugRender(mesh);
		}
		renderer::debugMeshes.clear();
	}

	void Editor::Release()
	{
		for (auto obj : mWidgets)
		{
			delete obj;
			obj = nullptr;
		}
		for (auto obj : mEditorObjects)
		{
			delete obj;
			obj = nullptr;
		}

		delete mDebugObjects[(UINT)eColliderType::Rect];
		delete mDebugObjects[(UINT)eColliderType::Circle];
	}

	void Editor::DebugRender(graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		Transform* tr = debugObj->GetComponent<Transform>();
		tr->SetPosition(mesh.position);
		tr->SetRotation(mesh.rotatation);


		if (mesh.type == eColliderType::Rect)
			tr->SetScale(mesh.scale);
		else
			tr->SetScale(Vector3(mesh.radius * 2)); 
		// 여기서 라디우스를 스케일로 설정해줌.
		// 원 메시를 만들때 반지름을 0.5로 설정했기 때문에, 실제 원의 반지름은 0.5다.
		// 만들때 반지름 1로 만들어라 ㅇㅇ;
		BaseRenderer* renderer = debugObj->GetComponent<BaseRenderer>();

		tr->FixedUpdate();

		Camera::SetGpuViewMatrix(renderer::mainCamera->GetViewMatrix());
		Camera::SetGpuProjectionMatrix(renderer::mainCamera->GetProjectionMatrix());

		debugObj->Render();
	}

}