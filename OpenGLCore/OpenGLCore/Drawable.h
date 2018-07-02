#pragma once

#include "CoreIncludes.h"
#include <glm/glm.hpp>
#include <string>

namespace Core
{
	enum DrawableType
	{
		DRAWABLE_SCENE,
		DRAWABLE_UI
	};

	class Drawable
	{
	public:
		Drawable();
		Drawable(DrawableType type);
		Drawable(DrawableType type, glm::vec3 _location);
		Drawable(DrawableType type, glm::vec3 _location, glm::vec3 _rotation);
		Drawable(DrawableType type, glm::vec3 _location, glm::vec3 _rotation, glm::vec3 _scale);

		~Drawable();

		virtual void Draw();
		void LoadShader(std::string name);

		DrawableType drawableType;
		GLuint shaderProgram;

		glm::mat4 transMatrix;
		
		glm::vec3 location;
		glm::vec3 rotation;
		glm::vec3 scale;

		virtual void Init(DrawableType type, glm::vec3 _location, glm::vec3 _rotation, glm::vec3 _scale);
	};
}
