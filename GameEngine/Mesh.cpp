#include "Mesh.h"

#include <GL\glew.h>

void Mesh::Draw(mat4 aModelViewMatrix)
{
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < Vertices.size(); i++)
	{
		auto vertex = aModelViewMatrix * vec4(Vertices[i], 1.0f);
		vertex.y /= vertex.w;
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}
	glEnd();
}