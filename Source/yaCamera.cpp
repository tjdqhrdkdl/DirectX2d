#include "yaCamera.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaApplication.h"
#include "yaSceneManager.h"
#include "yaBaseRenderer.h"


extern ya::Application application;

namespace ya
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		:Component(eComponentType::Camera)
		, mType(eProjectionType::Perspective)
		, mNear(1.0f)
		, mFar(100.0f)
		, mScale(1.0f)
		, mAspectRatio(1.0f)
		, mYFOV(XM_PI / 3)
	{
		mLayerMasks.set();
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
	}

	void Camera::Update()
	{
		RegisterCameraInRenderer();
	}

	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();	
	}

	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutout();
		renderTransparent();
	}

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		//�þ� ��� ���ϱ�. ���� ��ǥ to ī�޶� ��ǥ�� ��ȯ
		//���� ��ǥ�踦 ���� ��ǥ�� �ű�� �� W = SRT.
		//�� ��ȯ�� ���� ��ǥ�� ���� ��ǥ��� �ű��. Z =  W^-1 = (SRT)-1 �����
		//SCALE�� �����ϴ�, Z = (RT)^-1 = T^-1 * R^-1 = T^-1 * R^T

		Vector3 pos = tr->GetPosition();
		Vector3 forward = tr->Forward();
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();

		mView =
		{
			right.x, up.x,forward.x, 0,
			right.y, up.y,forward.y, 0,
			right.z, up.z,forward.z, 0,
			-pos.Dot(right),  -pos.Dot(up), -pos.Dot(forward), 1
		};
	}

	void Camera::CreateProjectionMatrix()
	{
		//���� ��� ���ϱ�. ���� ������ ���� ������ �����Ѵ�.
		//ī�޶��� �þ�(����ü ����)�� �ִ� ��ü���� ���� ����� 2���� ��ǥ�� ��ȯ�Ѵ�.
		//�������� ���� ��ü�� �Ÿ��� ���� ����� �Ÿ��� �̿��ϸ�, z���� ���Ͻ�Ű�Ƿ� z���� �����̵ȴ�.
		// ���� ������ ���� �ܰ��, ���� ������ �δ� �����.
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{	
			mProjection =
			{
				1 / (tan(mYFOV / 2) *mAspectRatio) , 0 , 0 , 0,
				0 ,			1 / tan(mYFOV / 2)		   , 0 , 0,
				0 ,	0 ,			 mFar / (mFar- mNear)      , 1,
				0 , 0 ,		-mNear*mFar / (mFar-mNear)     , 0,
			};
		}
		
		else
		{
			// z�� ������ ���� = ����ü�� �ҽ��� ������ ����. �׳� ��������, ����ȭ�� ���ش�.
			// ���� �����Ⱑ ���߿� ���ϱ� w�� 1�� �������.

			mProjection =
			{
				2 / width *100, 0 , 0 , 0,
				0 , 2 / height *100, 0 , 0,
				0 ,	0 ,			 1 / (mFar- mNear)      , 0,
				0 , 0 ,		mNear / (mNear-mFar)    , 1,
			};

		}
	}
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}
	void Camera::TurnLayerMask(eLayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}
	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetPlayScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				std::vector<GameObject*> gameObjects = layer.GetGameObjects();
				if (gameObjects.size() == 0)
					continue;

				for (GameObject* obj : gameObjects)

				{
					pushGameObjectToRenderingModes(obj);
				}
			}
		}
	}
	void Camera::renderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjects)
		{
			if(obj != nullptr)
				obj->Render();
		}
	}
	void Camera::renderCutout()
	{
		for (GameObject* obj : mCutoutGameObjects)
		{
			if (obj != nullptr)
				obj->Render();
		}
	}
	void Camera::renderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjects)
		{
			if (obj != nullptr)
				obj->Render();
		}
	}
	void Camera::pushGameObjectToRenderingModes(GameObject* gameObj)
	{
		BaseRenderer* renderer
			= gameObj->GetComponent<BaseRenderer>();
		if (renderer == nullptr)
			return;

		std::shared_ptr<Material> material = renderer->GetMaterial();
		//if (material == nullptr)
		//	continue;

		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case ya::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(gameObj);
			break;
		case ya::graphics::eRenderingMode::CutOut:
			mCutoutGameObjects.push_back(gameObj);
			break;
		case ya::graphics::eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(gameObj);
			break;
		default:
			break;
		}
	}
}