#ifndef MTLLOADER__HPP
#define MTLLOADER_HPP
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include "Material.h"
#include "Mesh.h"

#include <glm\glm.hpp>
using namespace glm;

bool loadMtl(
	const char *path,
	std::vector<shared_ptr<Material>> &materials
);

shared_ptr<Material> getDefaultMaterial();
#endif