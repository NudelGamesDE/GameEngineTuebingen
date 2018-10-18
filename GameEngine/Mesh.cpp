#include "Mesh.h"

#include <GL\glew.h>

void Mesh::Draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);

	for (int i = 0; i < Vertices.size(); i++)
	{
		auto vertex = Vertices[i];
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}
	glEnd();
}