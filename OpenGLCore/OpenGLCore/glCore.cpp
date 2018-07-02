#include "glCore.h"
#include "Drawable.h"
#include "MeshDrawable.h"
#include "ShaderManager.h"
#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_access.hpp>

using namespace Core;

std::vector<Drawable*> glCore::scenceDrawables;
std::vector<Drawable*> glCore::uiDrawables;
ShaderManager glCore::shaderManager;
Camera glCore::camera;
glm::vec2 glCore::windowSize;

void(*glCore::StartCallback)();
void(*glCore::UpdateCallback)(float);
void(*glCore::ExitCallback)();

unsigned long glCore::startTime = 0;
float glCore::deltaTime = 0.0166f;
unsigned long  glCore::frameStartTime = 0;
glm::vec2 glCore::mousePosition = glm::vec2(0, 0);

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

	StartCallback = start;
	UpdateCallback = update;
	ExitCallback = exit;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	SetWindowSize(MAXIMISED);

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

	SetMaximiseMode(MAXIMISED);

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
	glClearColor(CLEAR_COLOR);

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
	printf("Exiting glut\n");
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
		printf("OpenGL %s\n", glGetString(GL_VERSION));
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

		int w = (int)(glutGet(GLUT_SCREEN_WIDTH) * WINDOWED_START_SIZE_MULTIPLIER);
		int h = (int)(glutGet(GLUT_SCREEN_HEIGHT) * WINDOWED_START_SIZE_MULTIPLIER);

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
