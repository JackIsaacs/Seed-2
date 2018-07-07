#include "Application.h"

#include "glCore.h"
#include <glm/glm.hpp>

#include "UIDrawable.h"
#include "MeshDrawable.h"
#include "Math.h"


Core::Drawable* mesh;
Core::Drawable* uimesh;

///////////////////////////////////////////
// Start callback
// Runs at the first instance of the program
//
// Set up initialisers here

void OnStart()
{
	uimesh = new Core::UIDrawable();
	Core::glCore::AddToDrawables(uimesh);
	uimesh->scale /= 5.0f;

	mesh = new Core::MeshDrawable();
	Core::glCore::AddToDrawables(mesh);
}

///////////////////////////////////////////
// Update callback
// Runs each frame
//
// Update app logic here

void OnUpdate(float deltaTime)
{
	mesh->rotation.y += 100 * deltaTime;

	glm::vec2 pos = Math::ConvertMousePosToScreenSpace(Core::glCore::GetMousePosition());
	uimesh->location = glm::vec3(pos, 0.0f);
}

///////////////////////////////////////////
// Exit callback
// Runs when app is closed
//
// Clean up objects here

void OnExit()
{
	delete mesh;
	delete uimesh;
}
