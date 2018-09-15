#pragma once
#ifndef _Core_H_
#define _Core_H_

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#define MAX_LOADSTRING 100
#include "ConfigHandler.h"
#include "Resource.h"
#include "stdafx.h"
#include "GuiCore.h"


// GUI elements IDs
#define BTN_LOGIN 100

namespace NinguisFramework
{
	/**
	Core encapsulation of the whole system

	This class take windows messages. It initialize and cleans up the whole application.
	*/
	class Core
	{
	public:
		Core(const Core&);
		Core();
		~Core();

		enum GameState
		{
			LOGIN_OUT,
			UNINITIALIZED,
			RUNNING,
			MOUSE_INTERACTION,
			AIM_INTERACTION,
			CONNECTING,
			INGAME_MENU
		};
		static Core* getInstance();

		GameState gameState;
		bool Initialize(HINSTANCE);
		/**
		Handles messages passed from windows

		PARAM hwnd - Windows Handle class from win32 API
		PARAM uint - key code of the input
		PARAM wparam - unsigned int
		PARAM lparam - unsigned long
		*/
		LRESULT CALLBACK MessageHandeler(HWND, UINT, WPARAM, LPARAM);

		void Run();
		void setScreenHeight();
		void setScreenWidth();
		void InitializeWindows();
		void InitializeConsole();
		//virtual void keyEvent(Keyboard::KeyEvent evt, int key);
		//virtual bool mouseEvent(Mouse::MouseEvent evt, int x, int y, int wheelDelta);
		//virtual void resizeEvent(unsigned int width, unsigned int height);

		
		HWND userNameHWND;
		HWND passwordHWND;
		HWND version;
		HWND loginIn;
		HWND console;
		HWND connecting;

		TCHAR loginName[1024];
		TCHAR password[1024];

		int screenWidth, screenHeight;
		
		
	private:
		LPCTSTR mApplicationName;
		HINSTANCE mHinstance; /*Instance of this application to pass to CreateWindow*/
		HWND mHwnd;/*Windows Handle class from win32 API*/
		WCHAR szTitle[MAX_LOADSTRING];/*The title bar text*/
		WCHAR szWindowClass[MAX_LOADSTRING];/*The main window class name*/

		ConfigHandler * configHandler;
		GuiCore * guiCore;
	};

	/*
	FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)

	PURPOSE:  Processes messages for the main window.
	*/
	
	static LRESULT CALLBACK WindProc(HWND, UINT, WPARAM, LPARAM);
	static HBITMAP hBitmap = nullptr; //= LoadBitmap(GetModuleHandle(NULL),
	//	MAKEINTRESOURCE(IDB_INTRODUCEBACKGROUND));
	static NinguisFramework::Core * core = nullptr;
	//static LRESULT CALLBACK MyEditCallBckProcedure(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
}

#endif