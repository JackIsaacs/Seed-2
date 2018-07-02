#include "Camera.h"
#include "glCore.h"

using namespace Core;

Camera::Camera()
{
	location = glm::vec3(0, 0, 5);
}

Core::Camera::Camera(glm::vec3 _location)
{
	location = _location;
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetVPMatrix()
{
	return GetViewMatrix() * GetProjMatrix();
}

glm::mat4 Core::Camera::GetViewMatrix()
{
	float ratio = glCore::windowSize.x / glCore::windowSize.y;
	return glm::perspective(70.0f, ratio, 1.0f, 100.0f);
}

glm::mat4 Core::Camera::GetProjMatrix()
{
	return glm::lookAt(location, location + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}
