#include "Mesh.h"

#include <GL\glew.h>

float randFloat()
{
	return (rand() % 2001)*0.001f - 1.0f;
}
void Mesh::Draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(randFloat(), randFloat());
	glVertex2f(randFloat(), randFloat());
	glVertex2f(randFloat(), randFloat());
	glEnd();
}