#include "Camera.h"
#include "glCore.h"

using namespace Core;

Camera::Camera()
{
	location = CAMERA_DEFAULT_LOCATION;
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
	const float ratio = glCore::windowSize.x / glCore::windowSize.y;
	return glm::perspective(CAMERA_FOV, ratio, CAMERA_NEARCLIP, CAMERA_FARCLIP);
}

glm::mat4 Core::Camera::GetProjMatrix()
{
	return glm::lookAt(location, location + CAMERA_DIRECTION, UP);
}
