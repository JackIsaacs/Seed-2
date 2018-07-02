#pragma once

#include "Drawable.h"

#include "CoreIncludes.h"
#include <glm/glm.hpp>

namespace Core
{
	class MeshDrawable : public Drawable
	{
	public:
		MeshDrawable() : Drawable(DRAWABLE_SCENE) {};
		MeshDrawable(DrawableType type) : Drawable(type) {};
		MeshDrawable(DrawableType type, glm::vec3 _location) : Drawable(type, _location) {};
		MeshDrawable(DrawableType type, glm::vec3 _location, glm::vec3 _rotation) : Drawable(type, _location, _rotation) {};
		MeshDrawable(DrawableType type, glm::vec3 _location, glm::vec3 _rotation, glm::vec3 _scale) : Drawable(type, _location, _rotation, _scale) {};
	
		~MeshDrawable();

		void Draw();
	};
}
