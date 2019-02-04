#include "Terrain.h"
using namespace std;

/** \brief Constructor for a Terrain instance

The constructor generates all necessary renderers, materials and textures.
*/
Terrain::Terrain()
{
	TerrainRenderer = make_shared<Renderer>();
	TerrainMaterial = make_shared<Material>();
	HeightTexture = make_shared<Texture>();
	TerrainMaterial->HeightTexture = HeightTexture;
	TerrainMaterial->Shader = Shader::Terrain();
	TerrainRenderer->material = TerrainMaterial;
	SetHeightResolution(1);
	SetMeshResolution(1);
}

/** \brief Setter for height resolution

\param aResolution an integer being set as the CurrentHeight Resolution
*/
void Terrain::SetHeightResolution(int aResolution)
{
	CurrentHeightResolution = aResolution;
	Heights = shared_ptr<char[]>(new char[CurrentHeightResolution * CurrentHeightResolution]);
	for (int i = 0; i < CurrentHeightResolution * CurrentHeightResolution; i++)
		Heights[i] = 0;
	HeightTexture->Change2D(Heights.get(), CurrentHeightResolution, CurrentHeightResolution, 1);
}

/** \brief Setter for mesh resolution

\param aResolution an integer for setting the mesh resolution
*/
void Terrain::SetMeshResolution(int aResolution)
{
	vector<vec3> positions;
	vector<vec2> texCoords;
	vector<vec3> normals;

	auto addVertex = [&positions, &texCoords, &normals, aResolution](vec2 aPosition)
	{
		aPosition /= float(aResolution);
		positions.push_back(vec3(aPosition.x, 0.0, aPosition.y));
		texCoords.push_back(aPosition);
		normals.push_back(vec3(0, 1, 0));
	};

	for (int x = 0; x < aResolution; x++)
		for (int z = 0; z < aResolution; z++)
		{
			addVertex(vec2(x, z));
			addVertex(vec2(x, z + 1));
			addVertex(vec2(x + 1, z + 1));
			addVertex(vec2(x, z));
			addVertex(vec2(x + 1, z + 1));
			addVertex(vec2(x + 1, z));
		}

	TerrainRenderer->mesh = make_shared<Mesh>(positions, texCoords, normals);
}

/** \brief Add a float to char

\param aPrevious a char to be added to
\param aAdd a float to add
\return a char
*/
char addFloatToChar(char aPrevious, float aAdd)
{
	const auto New = float(unsigned char(aPrevious)) + aAdd * 255.0f;
	auto ret = char(max(0.0f, min(255.0f, New)));
	return ret;
}

/** \brief Setter for height values

\param aFunction
*/
void Terrain::SetHeightValues(std::function<float(vec3)> aFunction)
{
	auto transformMatrix = TerrainRenderer->transform.GetMatrix();
	for (int x = 0; x < CurrentHeightResolution; x++)
		for (int z = 0; z < CurrentHeightResolution; z++)
		{
			auto index = x + z * CurrentHeightResolution;
			auto worldPosition = transformMatrix * (vec4(x + 0.5f, 0, z + 0.5f, 0) / float(CurrentHeightResolution) + vec4(0, 0, 0, 1));
			Heights[index] = addFloatToChar(0, aFunction(worldPosition));
		}
	HeightTexture->Change2D(Heights.get(), CurrentHeightResolution, CurrentHeightResolution, 1);
}

/** \brief Add to height values

\param aFunction
*/
void Terrain::AddHeightValues(std::function<float(vec3)> aFunction)
{
	auto transformMatrix = TerrainRenderer->transform.GetMatrix();
	for (int x = 0; x < CurrentHeightResolution; x++)
		for (int z = 0; z < CurrentHeightResolution; z++)
		{
			auto index = x + z * CurrentHeightResolution;
			auto worldPosition = transformMatrix * (vec4(x + 0.5f, 0, z + 0.5f, 0) / float(CurrentHeightResolution) + vec4(0, 0, 0, 1));
			Heights[index] = addFloatToChar(Heights[index], aFunction(worldPosition));
		}
	HeightTexture->Change2D(Heights.get(), CurrentHeightResolution, CurrentHeightResolution, 1);
}

/** \brief Change height values

\param aFunction
*/
void Terrain::ChangeHeightValues(std::function<float(vec3, float)> aFunction)
{
	auto transformMatrix = TerrainRenderer->transform.GetMatrix();
	for (int x = 0; x < CurrentHeightResolution; x++)
		for (int z = 0; z < CurrentHeightResolution; z++)
		{
			auto index = x + z * CurrentHeightResolution;
			auto worldPosition = transformMatrix * (vec4(x + 0.5f, 0, z + 0.5f, 0) / float(CurrentHeightResolution) + vec4(0, 0, 0, 1));
			Heights[index] = addFloatToChar(0, aFunction(worldPosition, float(unsigned char(Heights[index])) / 255.0f));
		}
	HeightTexture->Change2D(Heights.get(), CurrentHeightResolution, CurrentHeightResolution, 1);
}

/** \brief Get terrain renderer

\return a terrain renderer
*/
std::shared_ptr<Renderer> Terrain::getRenderer() { return TerrainRenderer; }

/** \brief Get terrain material

\return a terrain material
*/
std::shared_ptr<Material> Terrain::getMaterial() { return TerrainMaterial; }