#include "MBApplication.h"
#include "MBInput.h"
#include "MBTime.h"
#include "MBSceneManager.h"
#include "MBTitleScene.h"
#include "MBCamera.h"
#include "MBCollisionManager.h"



namespace MB
{
	Application::Application() :
		mHwnd(NULL),
		mHdc(NULL),
		mWidth(0),
		mHeight(0),
		mBackHdc(NULL),
		mBackBuffer(NULL)
	{
	}
	Application::~Application()
	{
	}
	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);

		mWidth = 1280;
		mHeight = 720;


		RECT rect = { 0, 0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mHwnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);

		// ������ �ػ� ������ ��Ʈ�� ����
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);

		// ���� ������ ��Ʈ���� ����Ű�� DC ����
		mBackHdc = CreateCompatibleDC(mHdc);

		// ���� ������ ��Ʈ�ʰ� DC�� ���� ����
		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(defaultBitmap);

		Time::Initialize();
		Input::Initailize();
		Camera::Initialize();

		CollisionManager::Initialize();
		SceneManager::Initialize();

	}
	void Application::Run()
	{
		Update();
		Render();
	}
	void Application::Update()
	{
		Time::Update();
		Input::Update();
		Camera::Update();

		CollisionManager::Update();
		SceneManager::Update();
	}
	void Application::Render()
	{
		Time::Render(mBackHdc);

		HBRUSH brush = CreateSolidBrush(RGB(125, 125, 125));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, brush);
		Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);
		SelectObject(mBackHdc, oldBrush);
		DeleteObject(brush);

		CollisionManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);

		BitBlt(mHdc, 0, 0, mWidth, mHeight
			, mBackHdc, 0, 0, SRCCOPY);



	}
	void Application::Release()
	{
	}
}