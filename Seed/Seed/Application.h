#pragma once

enum TreeType
{
	TREETYPE_BROADLEAF,
	TREETYPE_PINE,
	TREETYPE_PALM
};

class Application
{
public:
	Application();
	~Application();

	void Init(HWND window, HINSTANCE hinstance, HMENU menubar);

	void SetActiveTreeWindow(TreeType treeType);

private:
	TreeType activeTreeType;

	HWND hWnd;
	HINSTANCE hInstance;
	HMENU hMenu;
};

