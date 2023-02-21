#pragma once
#include "yaComponent.h"

namespace ya
{
	using namespace math;
	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective,
			Orthographic,
		};

		Camera();
		~Camera();

		static Matrix& GetViewMatrix() { return View; }
		static Matrix& GetProjectionMatrix() { return Projection; }


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();


	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;
		
		float mAspectRatio;
		
		float mYFOV;

		float mNear;
		float mFar;
		float mScale;

		eProjectionType mType;
	};
}

