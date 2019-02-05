#include "Skybox.h"

/** \brief Constructor for a Skybox instance

This constructor saves the paths to the six textures used and loads the cube mesh and material.
\param posXFilename posX cubemap texture path
\param negXFilename negX cubemap texture path
\param posYFilename posy cubemap texture path
\param negYFilename negY cubemap texture path
\param posZFilename posZ cubemap texture path
\param negZFilename negZ cubemap texture path

*/
Skybox::Skybox(
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

/** \brief Get skybox renderer

This function creates shader, texture and renderer for the sky box and then returns the renderer
\return a shared pointer to the sky box renderer
*/
shared_ptr<Renderer> Skybox::getRenderer()
{
	if (cachedRenderer)return cachedRenderer;
	material->Shader = Shader::SkyBox();
	material->CubemapTexture = make_shared<Texture>(filenames);
	auto renderer = make_shared<Renderer>(mesh, material, transform);
	return cachedRenderer = renderer;
}