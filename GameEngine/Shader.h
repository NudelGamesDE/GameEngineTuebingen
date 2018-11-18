#ifndef _SHADER_H
#define _SHADER_H

#include <SDL_opengl.h>
#include <string>
#include <vector>
#include <memory>
#include <glm\glm.hpp>
using namespace glm;
using namespace std;

class Shader
{
	struct ShaderAttribute
	{
		GLuint Location;
		string Name;
	};
	GLuint Program;

	vector<shared_ptr<ShaderAttribute>> Attributes;

	shared_ptr<ShaderAttribute> FindAttribute(string aName);

	bool HasTesselation;

	bool DepthTest;
	bool AlphaBlend;
	bool FaceCulling;

public:
	Shader(string aVertex, string aFragment);

	void Bind();

	void Uniform1f(string aName, float aValue);
	void Uniform2f(string aName, vec2 aVec);
	void Uniform3f(string aName, vec3 aVec);
	void Uniform4f(string aName, vec4 aVec);
	void UniformMat4(string aName, mat4 aMat);
	void Uniform1i(string aName, int aI);
	~Shader();


	static shared_ptr<Shader> FlatTextured();
};

#else
class Shader;
#endif
