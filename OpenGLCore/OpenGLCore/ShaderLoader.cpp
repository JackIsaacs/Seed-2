#include "ShaderLoader.h"

#include <vector>
#include <fstream>

using namespace Core;

ShaderLoader::ShaderLoader()
{
}


ShaderLoader::~ShaderLoader()
{
}

GLuint Core::ShaderLoader::CreateProgram(const char * vertexShaderFilename, const char * fragmentShaderFilename)
{
	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		
		char s[128];
		sprintf_s(s, "Shader LINK ERROR\n%s", &program_log[0]);

		MessageBox(nullptr, s, "Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	return program;
}

std::string Core::ShaderLoader::ReadShader(const char * filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good())
	{
		char s[128];
		sprintf_s(s, "Can't read Shader\n%s", filename);

		MessageBox(nullptr, s, "Error", MB_ICONEXCLAMATION | MB_OK);
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint Core::ShaderLoader::CreateShader(GLenum shaderType, std::string source, const char * shaderName)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		
		char s[128];
		sprintf_s(s, "ERROR compiling shader: %s\n%s\n", shaderName, &shader_log[0]);

		MessageBox(nullptr, s, "Error", MB_ICONEXCLAMATION | MB_OK);

		return 0;
	}
	return shader;
}
