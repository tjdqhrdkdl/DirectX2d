#include "yaCamEffectScript.h"
#include "yaMaterial.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaResources.h"

namespace ya
{
	CamEffectScript::CamEffectScript()
	{
	}

	CamEffectScript::~CamEffectScript()
	{
	}

	void CamEffectScript::Initialize()
	{
	}

	void CamEffectScript::Update()
	{
	}

	void CamEffectScript::FixedUpdate()
	{
		shared_ptr<Material>  material = Resources::Find<Material>(L"CamEffectMaterial");
		if (material)
		{
			mFadeTime += Time::DeltaTime();
			if (mFadeTime > 2.0f)
				mFadeTime = 0;
			material->SetData(eGPUParam::Float, &mFadeTime);

		}
	}

	void CamEffectScript::Render()
	{
	}

}