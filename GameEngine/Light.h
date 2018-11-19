#ifndef LIGHT_H
#define LIGHT_H

#include<glm\glm.hpp>
using namespace glm;

class Light {
public:
	Light(vec3 aPosition, vec3 aColor, vec3 aDirection, int aType);
	vec3 Position;
	vec3 Color;
	vec3 Direction;
	int Type;
};

#else
class Light;
#endif
