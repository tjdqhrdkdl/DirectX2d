#include "yaApplication.h"
#include "yaRenderer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaResources.h"
#include "yaCollisionManager.h"
#include "yaObject.h"
namespace ya
{
	using namespace graphics;

	Application::Application()
	{

	}

	Application::~Application()
	{

	}



	void Application::Initialize()
	{
		Time::Initialize();
		Input::Initialize();

		renderer::Initialize();
		SceneManager::Initialize();
		CollisionManager::Initialize();
	}

	// ���� ���� ĳ���� �̵� ��� 
	// CPU UPDATE
	void Application::Update()
	{
		Time::Update();
		Input::Update();

		SceneManager::Update();
		CollisionManager::Update();

	}

	// GPU update
	void Application::FixedUpdate()
	{
		SceneManager::FixedUpdate();

		object::Release();
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		renderer::Render();

		//graphicDevice->Render();
	}
	// Running main engine loop
	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}
	void Application::Release()
	{
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = width;
			mHeight = height;


			ValidationMode vaildationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice_DX11>();
			graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}
