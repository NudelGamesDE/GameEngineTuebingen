#ifndef _RAY_H
#define _RAY_H

#include <limits>
#include <glm\vec3.hpp>
using namespace std;
using namespace glm;

struct Ray
{
	vec3 Origin = vec3(0, 0, 0);
	vec3 Direction = vec3(0, 0, 1);
	float Min = 0;
	float Max = numeric_limits<float>::max();
};

#else
struct Ray;
#endif