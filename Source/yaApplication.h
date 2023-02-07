#pragma once
#include "yaEngine.h"
#include "yaGraphics.h"
#include "yaGraphicDevice_DX11.h"

namespace ya 
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		virtual void Initialize();
		virtual void Update();

		virtual void FixedUpdate();
		virtual void Render();
		void Release();

		void SetWindow(HWND hwnd, UINT width, UINT height);

		HWND GetHwnd() { return mHwnd; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		bool initialized = false;
		std::unique_ptr<graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;

	};

}

