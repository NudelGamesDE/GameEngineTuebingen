#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <glm\glm.hpp>
#include "Material.h"
#include "Mesh.h"
#include "mtlLoader.h"

#include <glm\glm.hpp>
using namespace glm;

/** \brief functions for loading obj files
*/

bool loadObj(
	const char *path,
	std::vector<shared_ptr<Mesh>> &meshes,
	std::vector< shared_ptr<Material>> &materials,
	const char *mtlPath
);

bool loadObj(
	const char *path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec2> &out_uvs,
	std::vector<glm::vec3> &out_normals,
	const char *mtlPath
);
bool loadObj(
	const char *path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec2> &out_uvs,
	const char *mtlPath
);
bool loadObj(
	const char *path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec3> &out_normals,
	const char *mtlPath
);
bool loadObj(
	const char *path,
	std::vector<glm::vec3> &out_vertices,
	const char *mtlPath
);

#endif