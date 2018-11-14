#include "Mesh.h"

#include <GL\glew.h>

Mesh::Mesh(vector<vec3> aPositions, vector<vec2> aTextureCoords, vector<vec3> aNormals)
{
	Vertices = aPositions;
}

void Mesh::Draw(mat4 aModelViewMatrix)
{
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < Vertices.size(); i++)
	{
		auto vertex = aModelViewMatrix * vec4(Vertices[i], 1.0f);
		vertex /= vertex.w;
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}
	glEnd();
}


bool test(
	const vec3& aPosition0,
	const vec3& aPosition1,
	const vec3& aPosition2,
	const Ray& aRay,
	float& out)
{
	const vec3 edge1 = aPosition1 - aPosition0;
	const vec3 edge2 = aPosition2 - aPosition0;

	const vec3 pvec = cross(aRay.Direction, edge2);

	const float det = dot(edge1, pvec);
	const float invDet = 1.0f / det;

	const vec3 tvec = aRay.Origin - aPosition0;

	const float alpha = dot(tvec, pvec) * invDet;

	if (!(0.0f <= alpha) || alpha > 1.0f)
		return false;

	const vec3 qvec = cross(tvec, edge1);

	const float beta = dot(aRay.Direction, qvec) * invDet;

	if (!(0.0f <= beta) || alpha + beta > 1.0f)
		return false;

	const float t = dot(edge2, qvec) * invDet;

	if (aRay.Min >= t || aRay .Max <= t)
		return false;

	out = t;
	return true;
}

shared_ptr<RayHit> Mesh::Intersect(Ray& aRay)
{
	shared_ptr<RayHit> ret = nullptr;
	float distance;
	for (int i = 2; i < Vertices.size(); i += 3)
	{
		if (test(Vertices[i - 2], Vertices[i - 1], Vertices[i], aRay, distance))
		{
			auto hit = make_shared<RayHit>();
			hit->DirectionDistance = distance;
			if (ret)
			{
				if (ret->DirectionDistance > distance)
					ret = hit;
			}
			else
				ret = hit;
		}
	}
	return ret;
}