#include "ShadowMap.h"



ShadowMap::ShadowMap(shared_ptr<Light> light)
{
	lightInvDir = light->Direction; //maybe inverted?
	initBuffer();
	initTexture();
}


ShadowMap::~ShadowMap()
{
	glDeleteTextures(1, &textureID);
	glDeleteBuffers(1, &bufferID);
}

void ShadowMap::initBuffer()
{
	// Create and compile our GLSL program from the shaders
	shader = make_shared<Shader>(
			"void main()"
			"{"
			"	gl_Position = Projection * View * Model * vec4(position, 1.0);"
		"}",

		"void main()"
		"{"
		"	ColorOut = vec4(1.0,1.0,1.0, 1.0);"
		"}");
	
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;

	glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;


	shader->Bind();
	shader->UniformMat4("Projection", depthMVP);
	shader->UniformMat4("View", mat4(1));

}

void ShadowMap::initTexture()
{
	//initialize texture
}

void ShadowMap::draw()
{
	//send matrix to shader and draw
}