#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <functional>
#include "Renderer.h"

class Terrain
{
	std::shared_ptr<Renderer> TerrainRenderer;
	std::shared_ptr<Texture> HeightTexture;
	std::shared_ptr<Material> TerrainMaterial;
	std::shared_ptr<char[]> Heights;
	int CurrentHeightResolution;
public:
	Terrain();
	void SetHeightResolution(int aResolution);
	void SetMeshResolution(int aResolution);
	void SetHeightValues(std::function<float(vec3)> aFunction);
	void AddHeightValues(std::function<float(vec3)> aFunction);
	void ChangeHeightValues(std::function<float(vec3, float)> aFunction);
	std::shared_ptr<Renderer> getRenderer();
	std::shared_ptr<Material> getMaterial();
};

#else
class Terrain;
#endif