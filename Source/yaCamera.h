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

		void SetProjectionType(eProjectionType type) { mType = type; }
		void CreateViewMatrix();
		void CreateProjectionMatrix();

		void RegisterCameraInRenderer();		
		
		void TurnLayerMask(eLayerType layer, bool enable = true);
		void EnableLayerMasks() { mLayerMasks.set(); }
		void DisableLayerMasks() { mLayerMasks.reset(); }
	private:
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void pushGameObjectToRenderingModes(GameObject* gameObj);


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

		std::bitset<(UINT)eLayerType::End> mLayerMasks;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutoutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;
	};
}

