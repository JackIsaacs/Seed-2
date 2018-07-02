#pragma once

#include "CoreIncludes.h"

#include <string>

namespace Core
{
	class ShaderLoader
	{
	public:
		ShaderLoader();
		~ShaderLoader();

		GLuint CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename);

	private:
		std::string ReadShader(const char *filename);

		GLuint CreateShader(GLenum shaderType, std::string source, const char* shaderName);
	};
}
