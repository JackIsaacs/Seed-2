#include "Application.h"

#include "glCore.h"

#include "glCoreSettings.h"

int main(int argc, char **argv)
{
	//bool res = Core::glCore::Init(argc, argv, OnStart, OnUpdate, OnExit);
	//DBG_ASSERT(!res);

	Core::glCoreSettings settings;

	settings.LoadSettings();

	/*settings.startMaximised = true;
	settings.defaultWindowedSize.x = 1500;*/

	settings.SaveSettings();

	getchar();

	return 0;
}