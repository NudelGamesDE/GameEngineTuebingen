#ifndef _MESH_H
#define _MESH_H

#include <memory>
#include <vector>
#include <SDL_opengl.h>
#include <glm\vec3.hpp>
#include <glm\matrix.hpp>
#include "Ray.h"
#include "RayHit.h"
using namespace std;
using namespace glm;

class Mesh
{
	GLuint DataVBO;
	GLuint IndicesVBO;
	GLuint VAO;
	unsigned long IndicesCount;
public:
	Mesh(vector<vec3> aPositions, vector<vec2> aTextureCoords, vector<vec3> aNormals);
	vector<vec3> Vertices;
	vector<vec2> Uvs;
	vector<vec3> Normals;
	void Draw();
	shared_ptr<RayHit> Intersect(Ray& aRay);
	~Mesh();
};

#else
class Mesh;
#endif