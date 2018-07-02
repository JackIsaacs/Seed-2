#include "UIDrawable.h"
#include "glCore.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Math.h"

using namespace Core;

UIDrawable::~UIDrawable()
{
}

void Core::UIDrawable::Draw()
{
	float ratio = glCore::windowSize.y / glCore::windowSize.x;

	glm::vec3 s = scale;
	s.x *= ratio;

	Math::BuildTransformationMatrix(transMatrix, location, rotation, s);

	//glm::mat4 mvp = transMatrix;
	glm::mat4 mvp = transMatrix;


	glUseProgram(shaderProgram);

	GLint uniMvp = glGetUniformLocation(shaderProgram, "mvp");
	glUniformMatrix4fv(uniMvp, 1, GL_FALSE, &mvp[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
