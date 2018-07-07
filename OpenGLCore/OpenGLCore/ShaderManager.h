#pragma once

#include "CoreIncludes.h"

#include <map>
#include <string>

namespace Core
{
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		GLuint GetShader(std::string name);
		void LoadShader(std::string name, const char* vertPath, const char* fragPath);

		void ReleaseShaders();

	private:
		std::map<std::string, GLuint> shaderMap;
	};
}

