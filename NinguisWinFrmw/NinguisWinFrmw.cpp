// NinguisWinFrmw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Core.h"
//#include "Resource.h"

using namespace NinguisFramework;

int APIENTRY wWinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Core* core = new Core;

	core = Core::getInstance();
	if (core->Initialize(hInstance))
	{
		core->Run();
	}

    return 0;
}

