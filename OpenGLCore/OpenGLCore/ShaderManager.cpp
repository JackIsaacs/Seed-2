#include "ShaderManager.h"

#include "ShaderLoader.h"

using namespace Core;


ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

GLuint Core::ShaderManager::GetShader(std::string name)
{
	if (shaderMap.count(name) == 0)
	{
		char s[128];
		sprintf_s(s, "Shader: %s undefined", name.c_str());

		MessageBox(nullptr, s, "Error", MB_ICONEXCLAMATION | MB_OK);

		std::terminate();
	}

	return shaderMap[name];
}

void Core::ShaderManager::LoadShader(std::string name, const char * vertPath, const char * fragPath)
{
	if (shaderMap.count(name))
	{
		char s[128];
		sprintf_s(s, "Shader: %s defined more than once", name.c_str());

		MessageBox(nullptr, s, "Error", MB_ICONEXCLAMATION | MB_OK);

		std::terminate();
	}

	ShaderLoader sl;
	GLuint shader = sl.CreateProgram(vertPath, fragPath);

	shaderMap.insert(std::pair<std::string, GLuint>(name, shader));
}

void Core::ShaderManager::ReleaseShaders()
{
	for (auto const& x : shaderMap)
	{
		glDeleteShader(x.second);
	}

	shaderMap.clear();
}