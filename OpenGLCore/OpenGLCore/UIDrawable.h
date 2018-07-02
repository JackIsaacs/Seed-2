#pragma once

#include "Drawable.h"

#include "CoreIncludes.h"
#include <glm/glm.hpp>

namespace Core
{
	class UIDrawable : public Drawable
	{
	public:
		UIDrawable() : Drawable(DRAWABLE_UI) {};
		UIDrawable(DrawableType type) : Drawable(type) {};
		UIDrawable(DrawableType type, glm::vec3 _location) : Drawable(type, _location) {};
		UIDrawable(DrawableType type, glm::vec3 _location, glm::vec3 _rotation) : Drawable(type, _location, _rotation) {};
		UIDrawable(DrawableType type, glm::vec3 _location, glm::vec3 _rotation, glm::vec3 _scale) : Drawable(type, _location, _rotation, _scale) {};

		~UIDrawable();

		virtual void Draw();
	};
}
