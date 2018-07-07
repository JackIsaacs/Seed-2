#include "glCoreSettings.h"

#define SETTINGS_PATH "data/settings.json"

//////////////////////////////////////////
// Data keys
#define STARTMAXIMIZED		{ "window", "start_maximized" }
#define DEFAULTWINDOWEDSIZE	{ "window", "windowed_start_size" }
#define CLEARCOLOR			{ "renderer", "clear_color" }


//////////////////////////////////////////
// Fallback values
#define STARTMAXIMIZED_FALLBACK			false
#define DEFAULTWINDOWEDSIZE_FALLBACK	{ 800, 600 }
#define CLEARCOLOR_FALLBACK				{ 0.2f, 0.2f, 0.2f, 1.0f }


void Core::glCoreSettings::LoadSettings()
{
	if (LoadJSON(SETTINGS_PATH))
	{
		startMaximised			= GetValue<bool>(STARTMAXIMIZED);
		defaultWindowedSize		= GetVec2(DEFAULTWINDOWEDSIZE);
		clearColor				= GetVec4(CLEARCOLOR);
	}
}

void Core::glCoreSettings::SaveSettings()
{
	ApplyLoadedToJSONMap();
	JSONLoader::SaveSettings(); // Save data file to the stream
}

void Core::glCoreSettings::LoadFallback()
{
	println("Fallback settings loaded");

	startMaximised			= STARTMAXIMIZED_FALLBACK;
	defaultWindowedSize		= DEFAULTWINDOWEDSIZE_FALLBACK;
	clearColor				= CLEARCOLOR_FALLBACK;

	ApplyLoadedToJSONMap();
}

void Core::glCoreSettings::ApplyLoadedToJSONMap()
{
	SetValue(STARTMAXIMIZED,		startMaximised);
	SetVec2(DEFAULTWINDOWEDSIZE,	defaultWindowedSize);
	SetVec4(CLEARCOLOR,				clearColor);
}