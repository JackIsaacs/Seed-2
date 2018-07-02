#pragma once

#include "CoreIncludes.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace Core
{
	class Camera
	{
	public:
		Camera();
		Camera(glm::vec3 _location);
		~Camera();

		glm::mat4 GetVPMatrix();
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjMatrix();

		glm::vec3 location;
	};
}

