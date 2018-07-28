#include "stdafx.h"
#include "ConfigHandler.h"


ConfigHandler::ConfigHandler()
{
	ConfigPath = nullptr;

}


ConfigHandler::~ConfigHandler()
{
}

void ConfigHandler::LoadConfigFile()
{	
	result = SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, ConfigPath);
	if (FAILED(result))
	{
		//throw an exception?
	}
	
	std::wstring mywstring(LPCWSTR(ConfigPath));
	ConfigPath = ConfigPath + PROJECT_NAME;

	auto const& configDefines = ConfigDefines::instance();
	

}

void ConfigHandler::CreateConfigFile()
{
}

void ConfigHandler::SetToDefaults()
{
}
