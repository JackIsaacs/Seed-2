#pragma once

#include "JSONLoader.h"
#include "CoreIncludes.h"
#include <glm/glm.hpp>

namespace Core
{
	class glCoreSettings : public JSONLoader
	{
	public:
		bool startMaximised;
		glm::vec2 defaultWindowedSize;
		glm::vec4 clearColor;

		void LoadSettings();
		void SaveSettings();
		void LoadFallback();

	private:
		void ApplyLoadedToJSONMap();
	};
}
