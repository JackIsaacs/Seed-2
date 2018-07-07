#include "glCore.h"
#include "Drawable.h"
#include "MeshDrawable.h"
#include "ShaderManager.h"
#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include "glCoreSettings.h"

using namespace Core;

Core::ShaderManager Core::glCore::shaderManager;
Core::Camera Core::glCore::camera;
glm::vec2 Core::glCore::windowSize;
Core::glCoreSettings Core::glCore::settings;

void(*glCore::StartCallback)();
void(*glCore::UpdateCallback)(float);
void(*glCore::ExitCallback)();
unsigned long Core::glCore::startTime;
float Core::glCore::deltaTime;
unsigned long Core::glCore::frameStartTime;
glm::vec2 Core::glCore::mousePosition;
std::vector<Drawable*> Core::glCore::scenceDrawables;
std::vector<Drawable*> Core::glCore::uiDrawables;


glCore::glCore()
{
}


glCore::~glCore()
{
}

bool Core::glCore::Init(int argc, char ** argv, void(*start)(), void(*update)(float), void(*exit)())
{
	DBG_ASSERT(!start);
	DBG_ASSERT(!update);

	//////////////////////////////////////////////
	// Get settings
	settings.LoadSettings();

	//////////////////////////////////////////////

	StartCallback = start;
	UpdateCallback = update;
	ExitCallback = exit;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	SetWindowSize(settings.startMaximised);

	glutCreateWindow(WINDOW_TITLE);
	glewInit();
	glEnable(GL_DEPTH_TEST);

	DBG_ASSERT(!CheckOpenGLSupport());

	camera = Camera();
	shaderManager.LoadShader("default", "vert_shader.glsl", "frag_shader.glsl");

	glutDisplayFunc(Flip);
	glutReshapeFunc(ReshapeCallback);
	glutCloseFunc(CloseCallback);
	glutIdleFunc(UpdateGameLogic);
	glutPassiveMotionFunc(MousePassiveCallback);

	startTime = GetCurrentTime();

	StartCallback();

	SetMaximiseMode(settings.startMaximised);

	glutMainLoop();

	shaderManager.ReleaseShaders();

	return true;
}

void Core::glCore::AddToDrawables(Drawable * drawable)
{
	switch (drawable->drawableType)
	{
	case DRAWABLE_SCENE:
		scenceDrawables.push_back(drawable);
		break;
	case DRAWABLE_UI:
		uiDrawables.push_back(drawable);
		break;
	}
}

void Core::glCore::RemoveDrawable(Drawable * drawable)
{
	switch (drawable->drawableType)
	{
	case DRAWABLE_SCENE:
		RemoveFromDrawablesVector(&scenceDrawables, drawable);
		break;
	case DRAWABLE_UI:
		RemoveFromDrawablesVector(&uiDrawables, drawable);
		break;
	}
}

void Core::glCore::CleanDrawables()
{
	scenceDrawables.clear();
	uiDrawables.clear();
}

unsigned long Core::glCore::GetTime()
{
	unsigned long current = GetCurrentTime();
	return current - startTime;
}

glm::vec2 Core::glCore::GetMousePosition()
{
	return mousePosition;
}



void Core::glCore::Flip(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(settings.clearColor.r, 
		settings.clearColor.g, 
		settings.clearColor.b, 
		settings.clearColor.a);

	for (unsigned int i = 0; i < scenceDrawables.size(); ++i)
	{
		scenceDrawables[i]->Draw();
	}

	for (unsigned int i = 0; i < uiDrawables.size(); ++i)
	{
		uiDrawables[i]->Draw();
	}

	glutSwapBuffers();

	deltaTime = (GetTime() - frameStartTime) / 1000.0f;
}

void Core::glCore::ReshapeCallback(int w, int h)
{
	if (w < MINIMUM_WIDTH) glutReshapeWindow(MINIMUM_WIDTH, h);
	else if (h < MINIMUM_HEIGHT) glutReshapeWindow(w, MINIMUM_HEIGHT);

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	windowSize = { w, h };
}

void Core::glCore::CloseCallback(void)
{
	println("Exiting glut");
	glutLeaveMainLoop();

	ExitCallback();
}

void Core::glCore::MousePassiveCallback(int x, int y)
{
	mousePosition = { x ,y };
}

bool Core::glCore::CheckOpenGLSupport()
{
	if (!glewIsSupported(MINIMUM_GL_VERSION))
	{
		char s[128];
		sprintf_s(s, "OpenGL %s not supported\nCurrent version: %s", MINIMUM_GL_VERSION_STRING, glGetString(GL_VERSION));

		MessageBox(nullptr, s, "Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	else
	{
		println("OpenGL %s", glGetString(GL_VERSION));
		return true;
	}
}

void Core::glCore::RemoveFromDrawablesVector(std::vector<Drawable*>* vec, Drawable * drawable)
{
	auto it = std::find(vec->begin(), vec->end(), drawable);
	if (it != vec->end())
	{
		vec->erase(it);
	}
}

void Core::glCore::UpdateGameLogic()
{
	frameStartTime = GetTime();

	UpdateCallback(deltaTime);

	glutPostRedisplay();
}

void Core::glCore::SetWindowSize(bool maximised)
{
	if (maximised)
	{
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
		windowSize = { glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT) };
	}
	else
	{
		glutInitWindowPosition(10, 10);

		int w = settings.defaultWindowedSize.x;
		int h = settings.defaultWindowedSize.y;

		glutInitWindowSize(w, h);
		windowSize = { w, h };
	}
}

void Core::glCore::SetMaximiseMode(bool maximised)
{
	if (maximised)
	{
		HWND winHandle = FindWindow(0, "Seed");
		SetWindowLong(winHandle, GWL_STYLE, (GetWindowLong(winHandle, GWL_STYLE) | SW_MAXIMIZE));
		ShowWindow(winHandle, SW_MAXIMIZE);
	}
}


