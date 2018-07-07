#pragma once

#include "CoreIncludes.h"

#include <glm/glm.hpp>
#include <vector>

namespace Core
{
	class Drawable;
	class ShaderManager;
	class Camera;
	class glCoreSettings;

	class glCore
	{
		// Static stuff
	public:
		static ShaderManager shaderManager;
		static Camera camera;
		static glm::vec2 windowSize;

		static glCoreSettings settings;

	private:
		static void(*StartCallback)();
		static void(*UpdateCallback)(float);
		static void(*ExitCallback)();

		static unsigned long startTime;
		static float deltaTime;
		static unsigned long frameStartTime;
		static glm::vec2 mousePosition;
		static std::vector<Drawable*> scenceDrawables;
		static std::vector<Drawable*> uiDrawables;

	public:
		glCore();
		~glCore();

		static bool Init(int argc, char** argv, 
			void(*start)(), 
			void(*update)(float), 
			void(*exit)());

		//////////////////////////////////////////
		// Drawable management
		static void AddToDrawables(Drawable* drawable);
		static void RemoveDrawable(Drawable* drawable);
		static void CleanDrawables();

		//////////////////////////////////////////
		// Misc
		static unsigned long GetTime();
		static glm::vec2 GetMousePosition();

	private:

		//////////////////////////////////////////
		// Callbacks
		static void Flip(void);
		static void ReshapeCallback(int w, int h);
		static void CloseCallback(void);
		static void MousePassiveCallback(int x, int y);

		//////////////////////////////////////////
		// GL related
		static bool CheckOpenGLSupport();
		static void SetWindowSize(bool maximised);
		static void SetMaximiseMode(bool maximised);

		//////////////////////////////////////////
		// Game
		static void UpdateGameLogic();
		static void RemoveFromDrawablesVector(std::vector<Drawable*>* vec, Drawable* drawable);
	};
}

