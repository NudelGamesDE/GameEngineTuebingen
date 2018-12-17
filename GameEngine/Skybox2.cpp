#include "Skybox2.h"

Skybox2::Skybox2(
	const char* posXFilename,
	const char* negXFilename,
	const char* posYFilename,
	const char* negYFilename,
	const char* posZFilename,
	const char* negZFilename)
{

	filenames.push_back(posXFilename);
	filenames.push_back(negXFilename);
	filenames.push_back(posYFilename);
	filenames.push_back(negYFilename);
	filenames.push_back(posZFilename);
	filenames.push_back(negZFilename);

	vector<shared_ptr<Mesh>> cubeObj;
	vector<shared_ptr<Material>> cubeMtl;

	loadObj("../cube.obj", cubeObj, cubeMtl, "../cube.mtl");

	mesh = cubeObj[0];
	material = cubeMtl[0];
}

shared_ptr<Renderer> Skybox2::getRenderer() 
{
	material->Shader = Shader::SkyBox();
	material->ColorTexture = make_shared<Texture>(filenames);
	auto renderer = make_shared<Renderer>(mesh, material, transform);
	return renderer;
}