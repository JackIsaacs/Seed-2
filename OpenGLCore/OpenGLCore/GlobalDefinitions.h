#pragma once

// Vector Constants
#define UP							glm::vec3(0, 1, 0)
#define DOWN						glm::vec3(0, -1, 0)
#define LEFT						glm::vec3(-1, 0, 0)
#define RIGHT						glm::vec3(1, 0, 0)
#define FORWARD						glm::vec3(0, 0, 1)
#define BACK						glm::vec3(0, 0, -1)

// GL Constants
#define WINDOW_TITLE				"Seed"
#define MINIMUM_GL_VERSION			"GL_VERSION_4_0"
#define MINIMUM_GL_VERSION_STRING	"4.0"
#define MINIMUM_WIDTH				800
#define MINIMUM_HEIGHT				600
#define CLEAR_COLOR					0.2f, 0.2f, 0.2f, 1.0f
#define WINDOWED_START_SIZE_MUL		0.75f

// Camera Constants
#define CAMERA_DIRECTION			BACK
#define CAMERA_FOV					70.0f
#define CAMERA_NEARCLIP				1.0f
#define CAMERA_FARCLIP				100.0f
#define CAMERA_DEFAULT_LOCATION		glm::vec3(0, 0, 5);