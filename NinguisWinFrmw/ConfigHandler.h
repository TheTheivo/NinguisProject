#pragma once

#include <iostream>
#include <ShlObj_core.h>

#include "ConfigDefines.h"

class ConfigHandler
{
public:
	ConfigHandler();
	~ConfigHandler();
	void SetConfigFile();
	void ReadConfigFile();

private:
	void LoadConfigFile();
	void CreateConfigFile();
	void SetToDefaults();

	PWSTR* ConfigPath;
	
	HRESULT result;

};

