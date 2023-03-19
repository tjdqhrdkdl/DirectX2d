#include "yaAnimation.h"
#include "yaTime.h"
#include "yaRenderer.h"
namespace ya
{
	Animation::Animation()
	{
	}

	Animation::~Animation()
	{
	}

	int Animation::Update()
	{
		if (mbComplete)
			return -1;
		
		mTime += Time::DeltaTime();
		if (mTime > mSpriteSheet[mIndex].duration)
		{
			mTime = 0.0f;
			++mIndex;
			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = mSpriteSheet.size() - 1;
			}

			return mIndex;
		}

		return -1;
	}

	void Animation::FixedUpdate()
	{
	}

	void Animation::Render()
	{
	}

	void Animation::Reset()
	{
		mIndex = 0;
		mTime = 0;
		mbComplete = false;
	}

	void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
							, Vector2 leftTop, Vector2 size, Vector2 offset
							, UINT spriteLegth, float duration)
	{
		mAnimationName = name;
		mAtlas = atlas;

		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();


		for (size_t i = 0; i < spriteLegth; i++)
		{
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + size.x*i)/width, (leftTop.y)/height);
			sprite.size = Vector2(size.x / width, size.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.atlasSize = Vector2( width,height);

			mSpriteSheet.push_back(sprite);
		}





	}

	void Animation::BindShader()
	{
		mAtlas->BindShader(eShaderStage::PS, 0);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animator];

		renderer::AnimatorCB info = {};

		info.atlasSize = mSpriteSheet[mIndex].atlasSize;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.size = mSpriteSheet[mIndex].size;
		info.type = (UINT)eAnimationType::SecondDimension;

		cb->Bind(&info);
		cb->SetPipline(eShaderStage::PS);

	}

	void Animation::Clear()
	{
		mAtlas->Clear();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animator];
		renderer::AnimatorCB info = {};
		info.type = (UINT)eAnimationType::None;

		cb->Bind(&info);
		cb->SetPipline(eShaderStage::PS);

	}

}