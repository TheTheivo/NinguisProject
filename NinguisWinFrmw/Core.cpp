#include "stdafx.h"
#include "Core.h"

using namespace NinguisFramework;

Core::Core(const Core& another)
{
}

Core::Core()
{
	core = this;
	configHandler = new ConfigHandler;
	gameState = Core::UNINITIALIZED;
}

Core::~Core()
{
	core = nullptr;
	configHandler = nullptr;
}

Core* Core::getInstance()
{
	return core;	
}

void Core::Run()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;

	while (!done)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = true;
			if (!result)
			{
				done = true;
			}
		}

	}
}

bool Core::Initialize(HINSTANCE hInstance)
{
	this->mHinstance = hInstance;
	//TODO: repair in configHandler needed
	//configHandler->LoadConfigFile();
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_NINGUISWINFRMW, szWindowClass, MAX_LOADSTRING);
	setScreenHeight();
	setScreenWidth();
	
	InitializeWindows();
	//this->guiCore = new GuiCore();
	//bool guiResult = guiCore->Run();
	return true;
}

LRESULT Core::MessageHandeler(HWND, UINT, WPARAM, LPARAM)
{
	return LRESULT();
}

void Core::setScreenHeight()
{
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

void Core::setScreenWidth()
{
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

void Core::InitializeWindows()
{
	
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mHinstance;
	wcex.hIcon = LoadIcon(mHinstance, MAKEINTRESOURCE(IDI_NINGUISWINFRMW));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.cbSize = sizeof(WNDCLASSEX);

	RegisterClassExW(&wcex);
	//TODO: Re implement this to take info from configHandler
	if (FULL_SCREEN == "true")
	{
		try
		{
			mHwnd = CreateWindowW(szWindowClass,
				szTitle,
				WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
				0,
				0,
				screenWidth,
				screenHeight,
				nullptr,
				nullptr,
				mHinstance,
				nullptr);
		}
		catch (const std::exception&)
		{

		}
	}
	//TODO:: Needs polishing
	else
	{
		try
		{
			mHwnd = CreateWindowW(szWindowClass,
				szTitle,
				WS_OVERLAPPEDWINDOW,
				0,
				0,
				screenWidth,
				screenHeight,
				nullptr,
				nullptr,
				mHinstance,
				nullptr);
		}
		catch (const std::exception&)
		{

		}
	}

	ShowWindow(mHwnd, SW_SHOW);
	SetForegroundWindow(mHwnd);
	SetFocus(mHwnd);
	ShowCursor(true);
	UpdateWindow(mHwnd);
}


LRESULT CALLBACK NinguisFramework::WindProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		 core->userNameHWND = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
			 WS_CHILD | WS_VISIBLE,
			GetSystemMetrics(SM_CXSCREEN)/ 2, GetSystemMetrics(SM_CYSCREEN)/ 2, 300, 30,
			hWnd, (HMENU)1, nullptr, nullptr);
		 //SetWindowSubclass(core->userName, MyEditCallBckProcedure, 0, 0);
		 core->passwordHWND = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT(""),
			 WS_CHILD | WS_VISIBLE,
			 GetSystemMetrics(SM_CXSCREEN) / 2, (GetSystemMetrics(SM_CYSCREEN)/ 2)+60, 300, 30,
			 hWnd, (HMENU)2, nullptr, nullptr);

		 //TODO: Load this from config file
		 core->version = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("STATIC"), TEXT("0.0.1 (Alpha)"),
			 WS_CHILD | WS_VISIBLE,
			 10, core->screenHeight -120 , 300, 20,
			 hWnd, (HMENU)3, nullptr, nullptr);

		 core->loginIn = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Button"), TEXT("Log in"),
			 WS_CHILD | WS_VISIBLE,
			 GetSystemMetrics(SM_CXSCREEN) / 2, (GetSystemMetrics(SM_CYSCREEN) / 2) + 120, 300, 30,
			 hWnd, (HMENU)BTN_LOGIN, NULL, NULL);

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case BTN_LOGIN:
			GetWindowText(core->userNameHWND, core->loginName, 1024);
			GetWindowText(core->passwordHWND, core->password, 1024);

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case (WM_CHAR):
		switch (wParam)
		{
		case (VK_ESCAPE):
			if (core->gameState != Core::CONNECTING)
			{
				DestroyWindow(hWnd);
				break;
			}
		}
		break;
	case WM_PAINT:
	{
		//TODO: get it out of full path
		hBitmap = (HBITMAP) LoadImage(nullptr, (LPCWSTR)L"C:/Engine Building/NinguisProject/NinguisProject/NinguisWinFrmw/imgResources/IntroduceBackGround1900x1080.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HDC hdcInst, hdcBitmap;
		BITMAP bp;
		RECT r;

		// Create a memory device compatible with the above DC variable
		hdcBitmap = CreateCompatibleDC(hdc);
		// Select the new bitmap
		SelectObject(hdcBitmap, hBitmap);
		GetObject(hBitmap, sizeof(bp), &bp);
		// Get client coordinates for the StretchBlt() function
		GetClientRect(hWnd, &r);
		// stretch bitmap across client area
		StretchBlt(hdc, 0, 0, r.right - r.left, r.bottom - r.top, hdcBitmap, 0,
			0, bp.bmWidth, bp.bmHeight, SRCCOPY);
		// Cleanup
		DeleteDC(hdcBitmap);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
/*

LRESULT CALLBACK NinguisFramework::MyEditCallBckProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	if ((uMsg == WM_CHAR) && (wParam == VK_ESCAPE))
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}
*/