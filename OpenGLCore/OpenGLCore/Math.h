#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>


namespace Math
{
	void BuildTransformationMatrix(glm::mat4 &mat, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale);

	glm::vec2 ConvertMousePosToScreenSpace(glm::vec2 mousePos);

}