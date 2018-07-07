#include "Drawable.h"
#include "glCore.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Math.h"

using namespace Core;

Drawable::Drawable()
{
	Init(DRAWABLE_SCENE, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
}

Core::Drawable::Drawable(DrawableType type)
{
	Init(type, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
}

Core::Drawable::Drawable(DrawableType type, glm::vec3 _location)
{
	Init(type, _location, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
}

Core::Drawable::Drawable(DrawableType type, glm::vec3 _location, glm::vec3 _rotation)
{
	Init(type, _location, _rotation, glm::vec3(1, 1, 1));

}

Core::Drawable::Drawable(DrawableType type, glm::vec3 _location, glm::vec3 _rotation, glm::vec3 _scale)
{
	Init(type, _location, _rotation, _scale);
}

Drawable::~Drawable()
{
}

void Drawable::Draw()
{
	
}

void Core::Drawable::LoadShader(std::string name)
{
	shaderProgram = glCore::shaderManager.GetShader(name);
}

void Core::Drawable::Init(DrawableType type, glm::vec3 _location, glm::vec3 _rotation, glm::vec3 _scale)
{
	drawableType = type;

	location = _location;
	rotation = _rotation;
	scale = _scale;

	Math::BuildTransformationMatrix(transMatrix, location, rotation, scale);

	LoadShader("default");
}
