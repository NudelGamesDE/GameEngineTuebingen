#include <GL\glew.h>
#include "Shader.h"
#include <iostream>
using namespace std;

const string VertexBeginning =
"#version 400\n"

"uniform mat4 Model;"
"uniform mat4 Projection;"
"uniform mat4 View;"

"layout(location = 0)in vec3 position;"
"layout(location = 1)in vec2 texCoord;"
"layout(location = 2)in vec3 normal;";

const string FragmentBeginning =
"#version 400\n"

"uniform vec3 DiffuseColor;"

"out vec4 ColorOut;";


void CompileShader(GLuint Shader, string aSource)
{
	/*auto _source = aSource.c_str();
	glShaderSource(Shader, 1, &_source, NULL);
	glCompileShader(Shader);
*/
	GLint result = GL_FALSE;
	int logLength;

	auto _source = aSource.c_str();

	glShaderSource(Shader, 1, &_source, NULL);
	glCompileShader(Shader);


	glGetShaderiv(Shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &logLength);
	vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(Shader, logLength, NULL, &vertShaderError[0]);
	auto error = string(&vertShaderError[0]);
	if (!error.empty())
		cout << error << endl;
}

vector<string> GetAttributes()
{
	auto ret = vector<string>();
	ret.push_back("Model");
	ret.push_back("View");
	ret.push_back("InverseView");
	ret.push_back("Projection");
	ret.push_back("DiffuseColor");
	return ret;
}

Shader::Shader(string aVertex, string aFragment)
{
	auto attributes = GetAttributes();

	GLuint _vertShader = glCreateShader(GL_VERTEX_SHADER);
	CompileShader(_vertShader, VertexBeginning + aVertex);

	GLuint _fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	CompileShader(_fragShader, FragmentBeginning + aFragment);

	Program = glCreateProgram();
	glAttachShader(Program, _vertShader);
	glAttachShader(Program, _fragShader);
	glLinkProgram(Program);


	glDeleteShader(_vertShader);
	glDeleteShader(_fragShader);

	for (unsigned int i = 0; i < attributes.size(); i++)
	{
		auto _attribute = make_shared< ShaderAttribute>();
		_attribute->Name = attributes[i];
		_attribute->Location = glGetUniformLocation(Program, _attribute->Name.c_str());
		if (_attribute->Location != -1)
			Attributes.push_back(_attribute);
	}
}

void Shader::Bind()
{
	glUseProgram(Program);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
}






void Shader::Uniform1f(string aName, float aValue)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute != nullptr)
		glUniform1f(_attribute->Location, aValue);
}
void Shader::Uniform2f(string aName, vec2 aVec)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute != nullptr)
		glUniform2f(_attribute->Location, aVec.x, aVec.y);
}
void Shader::Uniform3f(string aName, vec3 aVec)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute != nullptr)
		glUniform3f(_attribute->Location, aVec.x, aVec.y, aVec.z);
}
void Shader::Uniform4f(string aName, vec4 aVec)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute != nullptr)
		glUniform4f(_attribute->Location, aVec.x, aVec.y, aVec.z, aVec.w);
}
void Shader::UniformMat4(string aName, mat4 aMat)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute != nullptr)
		glUniformMatrix4fv(_attribute->Location, 1, GL_FALSE, &aMat[0][0]);
}
void Shader::Uniform1i(string aName, int aI)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute != nullptr)
		glUniform1i(_attribute->Location, aI);
}


shared_ptr<Shader::ShaderAttribute> Shader::FindAttribute(string aName)
{
	for (unsigned int i = 0; i < Attributes.size(); i++)
	{
		auto _attribute = Attributes[i];
		if (_attribute->Name == aName)
			return _attribute;
	}
	return nullptr;
}

Shader::~Shader()
{
	glDeleteProgram(Program);
}