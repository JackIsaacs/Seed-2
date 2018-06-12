#include "stdafx.h"
#include "Seed.h"
#include "Application.h"
#include <stdio.h>


Application::Application()
{
}


Application::~Application()
{
}

void Application::Init(HWND window, HINSTANCE hinstance, HMENU menubar)
{
	hWnd = window;
	hInstance = hinstance;
	hMenu = menubar;
}

void Application::SetActiveTreeWindow(TreeType treeType)
{
	if (activeTreeType == treeType) return;
	activeTreeType = treeType;

	switch (treeType)
	{
	case TREETYPE_BROADLEAF:
		CheckMenuItem(hMenu, ID_TREETYPE_BROADLEAF, MF_CHECKED);
		CheckMenuItem(hMenu, ID_TREETYPE_PINE, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_TREETYPE_PALM, MF_UNCHECKED);

		SetActiveWindowPane(IDD_BROADLEAF_FORM, hInstance, BroadLeafCallback);
		break;
	case TREETYPE_PINE:
		CheckMenuItem(hMenu, ID_TREETYPE_BROADLEAF, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_TREETYPE_PINE, MF_CHECKED);
		CheckMenuItem(hMenu, ID_TREETYPE_PALM, MF_UNCHECKED);

		SetActiveWindowPane(IDD_PINE_FORM, hInstance, PineCallback);
		break;
	case TREETYPE_PALM:
		CheckMenuItem(hMenu, ID_TREETYPE_BROADLEAF, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_TREETYPE_PINE, MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_TREETYPE_PALM, MF_CHECKED);

		SetActiveWindowPane(IDD_PALM_FORM, hInstance, PalmCallback);
		break;
	}
}
