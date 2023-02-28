#include "cameraScript.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaGameObject.h"
#include "yaTime.h"

ya::cameraScript::cameraScript()
{
}

ya::cameraScript::~cameraScript()
{
}

void ya::cameraScript::Initialize()
{
}

void ya::cameraScript::Update()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();

	Vector3 pos = tr->GetPosition();

	if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
	{
		pos += 10.0f * tr->Right() * Time::DeltaTime();
	}
	else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
	{
		pos += 10.0f * -tr->Right() * Time::DeltaTime();
	}
	else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
	{
		pos += 10.0f * tr->Forward() * Time::DeltaTime();
	}
	else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
	{
		pos += 10.0f * -tr->Forward() * Time::DeltaTime();
	}
	else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
	{
		pos += 10.0f * tr->Up() * Time::DeltaTime();
	}
	else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
	{
		pos += 10.0f * -tr->Up() * Time::DeltaTime();
	}

	tr->SetPosition(pos);
}

void ya::cameraScript::FixedUpdate()
{
}

void ya::cameraScript::Render()
{
}
