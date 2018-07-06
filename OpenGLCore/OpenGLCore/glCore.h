#pragma once

#include "CoreIncludes.h"

#include <glm/glm.hpp>
#include <vector>

#define JSON_START_MAXIMISED "start_maximized"

namespace Core
{
	class Drawable;
	class ShaderManager;
	class Camera;
	class JSONLoader;
	
	class glCore
	{
	public:
		glCore();
		~glCore();

		static bool Init(int argc, char** argv, 
			void(*start)(), 
			void(*update)(float), 
			void(*exit)());

		static void AddToDrawables(Drawable* drawable);
		static void RemoveDrawable(Drawable* drawable);
		static void CleanDrawables();

		static ShaderManager shaderManager;
		static Camera camera;

		static glm::vec2 windowSize;

		static unsigned long GetTime();

		static glm::vec2 GetMousePosition();

		static JSONLoader settings;

	private:
		static unsigned long startTime;

		static void(*StartCallback)();
		static void(*UpdateCallback)(float);
		static void(*ExitCallback)();

		static void Flip(void);
		static void ReshapeCallback(int w, int h);
		static void CloseCallback(void);
		static void MousePassiveCallback(int x, int y);

		static std::vector<Drawable*> scenceDrawables;
		static std::vector<Drawable*> uiDrawables;

		static bool CheckOpenGLSupport();
		static void RemoveFromDrawablesVector(std::vector<Drawable*>* vec, Drawable* drawable);

		static void UpdateGameLogic();

		static void SetWindowSize(bool maximised);
		static void SetMaximiseMode(bool maximised);

		static float deltaTime;
		static unsigned long frameStartTime;
		static glm::vec2 mousePosition;
		static glm::vec2 defaultWindowedSize;
		static glm::vec4 clearColor;

	};
}

