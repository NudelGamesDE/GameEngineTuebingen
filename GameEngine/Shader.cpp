#include <GL\glew.h>
#include "Shader.h"
#include <iostream>
using namespace std;

const string VertexBeginning =
"#version 400\n"

"uniform mat4 Model;"
"uniform mat4 Projection;"
"uniform mat4 View;"
"uniform mat4 InverseView;"

"uniform vec3 lightPositions[16];"
"uniform vec3 lightColors[16];"
"uniform vec3 lightDirections[16];"
"uniform int lightTypes[16];"
"uniform int lightCount;"

"layout(location = 0)in vec3 position;"
"layout(location = 1)in vec2 texCoord;"
"layout(location = 2)in vec3 normal;";

const string FragmentBeginning =
"#version 400\n"

"uniform sampler2D ColorTexture;"
"uniform sampler2D NormalTexture;"
"uniform samplerCube CubemapTexture;"
"uniform vec3 DiffuseColor;"
"uniform vec3 SpecularColor;"
"uniform vec3 AmbientColor;"

"uniform vec3 lightPositions[16];"
"uniform vec3 lightColors[16];"
"uniform vec3 lightDirections[16];"
"uniform int lightTypes[16];"
"uniform int lightCount;"

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
	ret.push_back("SpecularColor");
	ret.push_back("AmbientColor");
	ret.push_back("ColorTexture");
	ret.push_back("NormalTexture");
	ret.push_back("CubemapTexture");
	ret.push_back("lightPositions");
	ret.push_back("lightColors");
	ret.push_back("lightDirections");
	ret.push_back("lightTypes");
	ret.push_back("lightCount");
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
		auto _attribute = make_shared<ShaderAttribute>();
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
	if (_attribute)
		glUniform1f(_attribute->Location, aValue);
}
void Shader::Uniform2f(string aName, vec2 aVec)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute)
		glUniform2f(_attribute->Location, aVec.x, aVec.y);
}
void Shader::Uniform3f(string aName, vec3 aVec)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute)
		glUniform3f(_attribute->Location, aVec.x, aVec.y, aVec.z);
}
void Shader::Uniform4f(string aName, vec4 aVec)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute)
		glUniform4f(_attribute->Location, aVec.x, aVec.y, aVec.z, aVec.w);
}
void Shader::UniformMat4(string aName, mat4 aMat)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute)
		glUniformMatrix4fv(_attribute->Location, 1, GL_FALSE, &aMat[0][0]);
}
void Shader::Uniform1i(string aName, int aI)
{
	auto _attribute = FindAttribute(aName);
	if (_attribute)
		glUniform1i(_attribute->Location, aI);
}

void Shader::UniformLights(vector<vec3> aPositions, vector<vec3> aColor, vector<vec3> aDirection, vector<int> aType)
{
	auto minSize = min((int)min(min(aPositions.size(), aColor.size()), min(aDirection.size(), aType.size())), 16);
	GLfloat positionData[16 * 3];
	GLfloat colorData[16 * 3];
	GLfloat directionData[16 * 3];
	GLint typeData[16];

	for (auto i = 0; i < minSize; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			positionData[i * 3 + j] = aPositions[i][j];
			colorData[i * 3 + j] = aColor[i][j];
			directionData[i * 3 + j] = aDirection[i][j];
		}
		typeData[i] = aType[i];
	}

	auto positionAttribute = FindAttribute("lightPositions");
	auto colorAttribute = FindAttribute("lightColors");
	auto directionAttribute = FindAttribute("lightDirections");
	auto typeAttribute = FindAttribute("lightTypes");
	auto countAttribute = FindAttribute("lightCount");
	if (positionAttribute)glUniform3fv(positionAttribute->Location, 16, positionData);
	if (colorAttribute)glUniform3fv(colorAttribute->Location, 16, colorData);
	if (directionAttribute)glUniform3fv(directionAttribute->Location, 16, directionData);
	if (typeAttribute)glUniform1iv(typeAttribute->Location, 16, typeData);
	if (countAttribute)glUniform1i(countAttribute->Location, minSize);
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

shared_ptr<Shader> FlatTexturedShader;
shared_ptr<Shader> Shader::FlatTextured()
{
	if (!FlatTexturedShader)
	{
		FlatTexturedShader = make_shared<Shader>(
			"out vec2 VTexCoord;"
			"void main()"
			"{"
			"	gl_Position = Projection * View * Model * vec4(position, 1.0);"
			"	VTexCoord = texCoord;"
			"}",

			"in vec2 VTexCoord;"
			"void main()"
			"{"
			"	ColorOut = vec4(texture2D(ColorTexture, VTexCoord).xyz * DiffuseColor, 1.0);"
			"}");
	}
	return FlatTexturedShader;
}


shared_ptr<Shader> BlinnPhongTexturedShader;
shared_ptr<Shader> Shader::BlinnPhongTextured()
{
	if (!BlinnPhongTexturedShader)
	{
		BlinnPhongTexturedShader = make_shared<Shader>(
			"out vec3 VNormal;"
			"out vec3 VToCamera;"
			"out vec2 VTexCoord;"
			"out vec3 VToLight[16];"

			"void main()"
			"{"
			"	vec4 worldPos = Model * vec4(position, 1.0);"
			"	gl_Position = Projection * View * worldPos;"

			"	for (int i = 0; i < lightCount; i++)"
			"	{"
			"		if (lightTypes[i] == 1)"
			"			VToLight[i] = lightPositions[i] - worldPos.xyz;"
			"		else"
			"			VToLight[i] = -lightDirections[i];"
			"	}"
			"	VNormal = (Model * vec4(normal, 0.0)).xyz;"

			"	VToCamera = (InverseView * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPos.xyz;"
			"	VTexCoord = texCoord;"
			"}",

			"in vec3 VNormal;"
			"in vec3 VToCamera;"
			"in vec2 VTexCoord;"
			"in vec3 VToLight[16];"

			"void main()"
			"{"
			"	vec3 toCamera = normalize(VToCamera);"
			"	vec3 unitNormal = normalize(VNormal);"
			"	float specM = 64.0;"
			"	vec3 spec = vec3(0.0, 0.0, 0.0);"
			"	vec3 diff = vec3(0.0, 0.0, 0.0);"
			"	for (int i = 0; i < lightCount; i++)"
			"	{"
			"		vec3 toLight = normalize(VToLight[i]);"
			"		vec3 h = normalize(toCamera + toLight);"
			"		float angleH = clamp(dot(h, unitNormal), 0.0, 1.0);"
			"		spec += (specM + 8.0) / 8.0 * pow(angleH, specM);"
			"		diff += clamp(dot(unitNormal, toLight), 0.0, 1.0);"
			"	}"

			"	ColorOut = vec4(spec * SpecularColor + (diff * DiffuseColor + AmbientColor) * texture2D(ColorTexture, VTexCoord).xyz, 1.0);"
			"}");
	}
	return BlinnPhongTexturedShader;
}

shared_ptr<Shader> SkyBoxShader;
shared_ptr<Shader> Shader::SkyBox() {
	if (!SkyBoxShader) {
		SkyBoxShader = make_shared<Shader>(
			"out vec3 TexCoords;"

			"void main()"
			"{"
			"	TexCoords = position;"
			"	vec4 pos = Projection * View * Model * vec4(position, 1.0);"
			"	gl_Position = pos.xyww;"
			"}",

			"in vec3 TexCoords;"

			"void main()"
			"{"
			"	ColorOut = texture(CubemapTexture, TexCoords);"
			"}");
	}
	return SkyBoxShader;
}