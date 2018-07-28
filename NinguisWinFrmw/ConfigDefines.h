#pragma once

#include <iostream>
#include "SingletonTemplate.h"
#include <string>

const LPCWSTR PROJECT_NAME = L""

class ConfigDefines final : public SingletonTemplate<ConfigDefines>
{
public:
	ConfigDefines(token);
	~ConfigDefines();

	struct ConfigVariables
	{
		std::string fullScreen;
	};

	ConfigVariables configVariables;
};

