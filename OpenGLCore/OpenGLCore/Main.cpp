#include "Application.h"

#include "glCore.h"

int main(int argc, char **argv)
{
	bool res = Core::glCore::Init(argc, argv, OnStart, OnUpdate, OnExit);
	DBG_ASSERT(!res);

	return 0;
}