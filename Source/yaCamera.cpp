#include "yaCamera.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaApplication.h"

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
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
	}

	void Camera::Update()
	{
	}

	void Camera::FixedUpdate()
	{
		View = mView;
		Projection = mProjection;
		CreateViewMatrix();
		CreateProjectionMatrix();	
	}

	void Camera::Render()
	{

	}

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		//�þ� ��� ���ϱ�. ���� ��ǥ to ī�޶� ��ǥ�� ��ȯ
		//���� ��ǥ�踦 ���� ��ǥ�� �ű�� �� W = SRT.
		//�� ��ȯ�� ���� ��ǥ�� ���� ��ǥ��� �ű��. W = (SRT)-1 �����
		//SCALE�� �����ϴ�, W= (RT)^-1 = T^-1 * R^-1 = T^-1 * R^T

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
			mFar = 1;
			mNear = 0;
			mProjection =
			{
				2 / width, 0 , 0 , 0,
				0 , 2 / height, 0 , 0,
				0 ,	0 ,	 1, 0,
				0 , 0 ,	0 , 1,
			};
		}
	}
}