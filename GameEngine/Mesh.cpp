#include <GL\glew.h>
#include "Mesh.h"


Mesh::Mesh(vector<vec3> aPositions, vector<vec2> aTextureCoords, vector<vec3> aNormals)
{
	Vertices = aPositions;

	glGenBuffers(1, &DataVBO);
	glGenBuffers(1, &IndicesVBO);

	auto DataCount = min(aPositions.size(), min(aTextureCoords.size(), aNormals.size())) * 8;
	auto Data = shared_ptr<float[]>(new float[DataCount]);
	for (unsigned long i = 0; i < DataCount / 8; i++)
	{
		Data.get()[i * 8] = aPositions[i].x;
		Data.get()[i * 8 + 1] = aPositions[i].y;
		Data.get()[i * 8 + 2] = aPositions[i].z;
		Data.get()[i * 8 + 3] = aTextureCoords[i].x;
		Data.get()[i * 8 + 4] = aTextureCoords[i].y;
		Data.get()[i * 8 + 5] = aNormals[i].x;
		Data.get()[i * 8 + 6] = aNormals[i].y;
		Data.get()[i * 8 + 7] = aNormals[i].z;
	}

	glBindBuffer(GL_ARRAY_BUFFER, DataVBO);
	glBufferData(GL_ARRAY_BUFFER, DataCount * 4, Data.get(), GL_DYNAMIC_DRAW);

	IndicesCount = (unsigned long)aPositions.size() * 8;
	auto Indices = shared_ptr<unsigned long[]>(new unsigned long[IndicesCount]);
	for (unsigned long i = 0; i < IndicesCount; i++)
		Indices.get()[i] = i;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesCount * 4, Indices.get(), GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, DataVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * 4, (const void*)(0 * 4));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * 4, (const void*)(3 * 4));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * 4, (const void*)(5 * 4));
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glDeleteBuffers(1, &DataVBO);
	glDeleteBuffers(1, &IndicesVBO);
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

	if (aRay.Min >= t || aRay.Max <= t)
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