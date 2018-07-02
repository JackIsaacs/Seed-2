#include "MeshDrawable.h"
#include "glCore.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Math.h"

using namespace Core;

MeshDrawable::~MeshDrawable()
{
}

void Core::MeshDrawable::Draw()
{
	Math::BuildTransformationMatrix(transMatrix, location, rotation, scale);

	glm::mat4 mvp = glCore::camera.GetVPMatrix() * transMatrix;

	glUseProgram(shaderProgram);

	GLint uniMvp = glGetUniformLocation(shaderProgram, "mvp");
	glUniformMatrix4fv(uniMvp, 1, GL_FALSE, &mvp[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}


