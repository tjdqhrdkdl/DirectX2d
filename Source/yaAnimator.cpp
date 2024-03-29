#include "yaAnimator.h"

namespace ya
{
	Animator::Animator()
		:Component(eComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mPlayAnimation(nullptr)
		, mbLoop(false)
	{
	}

	Animator::~Animator()
	{
		for (auto anim : mAnimations)
		{
			delete anim.second;
			anim.second = nullptr;
		}

		for (auto evt : mEvents)
		{
			delete evt.second;
			evt.second = nullptr;
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mPlayAnimation == nullptr)
			return;
		int spriteIndex = mPlayAnimation->Update();
		Events* events = FindEvents(mPlayAnimation->GetAnimationName());
		if (mPlayAnimation->IsComplete())
		{
			if(events)
				events->mCompleteEvent();

			if (mbLoop)
				mPlayAnimation->Reset();
		}

		if (spriteIndex != -1
			&& events->mEvents[spriteIndex].mEvent)
		{
			events->mEvents[spriteIndex].mEvent();
		}

	}

	void Animator::FixedUpdate()
	{
	}

	void Animator::Render()
	{
	}

	bool Animator::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
						, Vector2 leftTop, Vector2 size, Vector2 offset
						, UINT spriteLegth, float duration)
	{
		if (atlas == nullptr)
			return false;
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return false;


		animation = new Animation();
		animation->Create(name, atlas, leftTop, size, offset, spriteLegth, duration, this);
		if (animation)
		{
			mAnimations.insert(std::make_pair(name, animation));
			Events* events = new Events();
			events->mEvents.resize(spriteLegth);
			mEvents.insert(std::make_pair(name, events));
		}
		else
			return false;

	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;
		return iter->second;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);
		if (iter == mEvents.end())
			return nullptr;
		return iter->second;
	}

	void Animator::Play(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = mPlayAnimation;
		Events* events = nullptr;
		if (prevAnimation)
			events = FindEvents(prevAnimation->GetAnimationName());

		if (events)
			events->mEndEvent();

		mPlayAnimation = FindAnimation(name);
		mPlayAnimation->Reset();
		mbLoop = loop;

		events = FindEvents(mPlayAnimation->GetAnimationName());

		if (events)
			events->mStartEvent();
		
	}

	void Animator::Binds()
	{
		if(mPlayAnimation)
			mPlayAnimation->BindShader();
	}

	void Animator::Clear()
	{
		if (mPlayAnimation)
			mPlayAnimation->Clear();
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mStartEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{

		Events* events = FindEvents(name);

		return events->mCompleteEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{

		Events* events = FindEvents(name);

		return events->mEndEvent.mEvent;
	}

	std::function<void()>& Animator::GetEvent(const std::wstring& name, UINT index)
	{
		Events* events = FindEvents(name);

		return events->mEvents[index].mEvent;
	}

}