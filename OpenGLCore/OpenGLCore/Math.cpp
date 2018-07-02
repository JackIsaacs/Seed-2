#include "Math.h"

#include "glCore.h"
#include "Camera.h"

void Math::BuildTransformationMatrix(glm::mat4 & mat, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale)
{
	mat = glm::mat4();

	mat = glm::translate(mat, location);

	mat *= glm::rotate(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	mat *= glm::rotate(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	mat *= glm::rotate(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

	mat = glm::scale(mat, scale);
}

glm::vec2 Math::ConvertMousePosToScreenSpace(glm::vec2 mousePos)
{
	mousePos.x /= Core::glCore::windowSize.x;
	mousePos.y /= Core::glCore::windowSize.y;

	mousePos.x = (mousePos.x * 2) - 1;
	mousePos.y = -((mousePos.y * 2) - 1);

	return mousePos;
}