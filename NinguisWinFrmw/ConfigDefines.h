

#include <iostream>
#include "SingletonTemplate.h"
#include <string>

namespace NinguisFramework
{

	const std::string PROJECT_NAME = "NinguisProject";
	const std::string CONFIG_FILE = "\\config.txt";

	const std::string FULL_SCREEN = "true";


	class ConfigDefines final : public SingletonTemplate<ConfigDefines>
	{
	public:
		ConfigDefines(token);
		~ConfigDefines();

		struct ConfigVariables
		{
			std::string fullScreen;
		};

		ConfigVariables* configVariables;
	};
}