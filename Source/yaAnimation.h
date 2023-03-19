#pragma once
#include "yaEntity.h"
#include "yaTexture.h"

namespace ya
{
	using namespace math;
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;

			Sprite()
				: leftTop(0.0f, 0.0f)
				, size(0.0f, 0.0f)
				, offset(0.0f, 0.0f)
				, atlasSize(0.0f)
				, duration(0.1f)
			{

			}
		};
		Animation();
		~Animation();

		int Update();
		void FixedUpdate();
		void Render();

		void Reset();
		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
					, Vector2 leftTop, Vector2 size, Vector2 offset
					, UINT spriteLegth, float duration);

		void BindShader();
		void Clear();

		std::wstring GetAnimationName() { return mAnimationName; }
		bool IsComplete() { return mbComplete; }

	

	private:
		class Animator* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<Texture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;

	};
}