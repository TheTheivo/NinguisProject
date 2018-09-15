#pragma once
#pragma comment(lib, "comsuppw")
#include <iostream>
#include <shlobj.h>

#include "ConfigDefines.h"

namespace NinguisFramework
{
	class ConfigHandler
	{
	public:
		ConfigHandler();
		~ConfigHandler();
		void LoadConfigFile();
		void SetConfigFile();
		std::string returnSetting();
	private:
		bool CreateConfigFile();
		bool SetToDefaults();
		void ReadConfigFile();
		bool CreateUserInfoFolder();

		PWSTR* dirUserDoc;
		LPCSTR dirProjectSettings;
		HRESULT result;
		bool procedureResult;
		HANDLE configFileHandle;

	};
}