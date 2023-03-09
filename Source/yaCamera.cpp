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
		//시야 행렬 구하기. 세계 좌표 to 카메라 좌표계 변환
		//국소 좌표계를 세계 좌표로 옮기는 식 W = SRT.
		//본 변환은 세계 좌표를 국소 좌표계로 옮긴다. Z =  W^-1 = (SRT)-1 역행렬
		//SCALE은 동일하니, Z = (RT)^-1 = T^-1 * R^-1 = T^-1 * R^T

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
		//투영 행렬 구하기. 직교 투영과 원근 투영을 구분한다.
		//카메라의 시야(절두체 내부)에 있는 물체들을 투영 평면의 2차원 좌표로 전환한다.
		//원점으로 부터 물체의 거리와 투영 평면의 거리비를 이용하며, z값을 통일시키므로 z축이 기준이된다.
		// 원근 나누기 이전 단계로, 투영 공간에 두는 행렬임.
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
			// z축 영향이 없다 = 절두체나 소실점 개념이 없다. 그냥 가져오되, 정규화만 해준다.
			// 원근 나누기가 나중에 들어가니까 w를 1로 맞춰야함.

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