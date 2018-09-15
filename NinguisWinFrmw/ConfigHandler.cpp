#include "stdafx.h"
#include "ConfigHandler.h"


using namespace NinguisFramework;

ConfigHandler::ConfigHandler()
{
	dirUserDoc = nullptr;
	dirProjectSettings = nullptr;
	procedureResult = false;
	configFileHandle = nullptr;
}


ConfigHandler::~ConfigHandler()
{
}
 
void ConfigHandler::SetConfigFile()
{
}


std::string ConfigHandler::returnSetting()
{
	//auto const& configDefines = ConfigDefines::instance();
	return ConfigDefines::instance().configVariables->fullScreen;
}

bool ConfigHandler::CreateConfigFile()
{
	//change to copy file from config file inside data
	std::string buffer;
	buffer = "FullScreen " + FULL_SCREEN;
	LPCVOID lpBuffer = LPCVOID(buffer.c_str());
	DWORD bytesWritten;

	configFileHandle = CreateFile(LPCWSTR(CONFIG_FILE.c_str()), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_NEW, FILE_ATTRIBUTE_ARCHIVE, nullptr);
	if (configFileHandle == nullptr)
	{
		return false;
	}
	procedureResult = WriteFile(configFileHandle, lpBuffer, strlen(buffer.c_str()), &bytesWritten, nullptr);
	if (procedureResult == false)
	{
		return false;
	}
	return true;
}

bool ConfigHandler::SetToDefaults()
{
	return false;
}

void ConfigHandler::ReadConfigFile()
{

}

bool ConfigHandler::CreateUserInfoFolder()
{
	return false;
}

void ConfigHandler::LoadConfigFile()
{	
	result = SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, nullptr, dirUserDoc);
	if (FAILED(result))
	{
		//throw an exception?
	}
	
	dirProjectSettings = LPCSTR(dirUserDoc);
	std::string(dirProjectSettings).append(PROJECT_NAME);// .c_str;  maybe it will be needed later

	DWORD attributes = GetFileAttributes(LPCTSTR(dirProjectSettings));
	if (INVALID_FILE_ATTRIBUTES == attributes)
	{
		attributes = CreateDirectory(LPCTSTR(dirProjectSettings), nullptr);
		if (INVALID_FILE_ATTRIBUTES == attributes)
		{
			//throw an exception
		}
	}

	std::string(dirProjectSettings).append(CONFIG_FILE);// .c_str; maybe it will be needed later

	attributes = GetFileAttributes(LPCTSTR(dirProjectSettings));

	if (INVALID_FILE_ATTRIBUTES == attributes)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
			procedureResult = CreateConfigFile();
		if (procedureResult == false)
		{
			//throw an exception
		}
	}

	auto const& configDefines = ConfigDefines::instance();
	
	// TODO: setup struct from file
	configDefines.configVariables->fullScreen = std::string("true");
}

