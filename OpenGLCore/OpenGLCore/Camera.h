#pragma once

#include "CoreIncludes.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace Core
{
	/*!
	 * \class Camera
	 *
	 * \brief Provides view and projection matrices based on the camera position, 
	 looking into the -Z
	 * 
	 * \author jacki
	 * \date July 2018
	 */
	class Camera
	{
	public:
		//************************************
		// Method:    Camera
		// FullName:  Core::Camera::Camera
		// Access:    public 
		// Qualifier:
		// Returns:   
		//************************************
		Camera();

		//************************************
		// Method:    Camera
		// FullName:  Core::Camera::Camera
		// Access:    public 
		// Qualifier:
		// Parameter: glm::vec3 _location
		// Returns:   
		//************************************
		Camera(glm::vec3 _location);

		//************************************
		// Method:    ~Camera
		// FullName:  Core::Camera::~Camera
		// Access:    public 
		// Qualifier:
		// Returns:   
		//************************************
		~Camera();

		//************************************
		// Method:    GetVPMatrix
		// FullName:  Core::Camera::GetVPMatrix
		// Access:    public 
		// Qualifier:
		// Returns:   glm::mat4
		//************************************
		glm::mat4 GetVPMatrix();

		//************************************
		// Method:    GetViewMatrix
		// FullName:  Core::Camera::GetViewMatrix
		// Access:    public 
		// Qualifier:
		// Returns:   glm::mat4
		//************************************
		glm::mat4 GetViewMatrix();

		//************************************
		// Method:    GetProjMatrix
		// FullName:  Core::Camera::GetProjMatrix
		// Access:    public 
		// Qualifier:
		// Returns:   glm::mat4
		//************************************
		glm::mat4 GetProjMatrix();

		// The camera's current location in 3D space
		glm::vec3 location; 
	};
}

