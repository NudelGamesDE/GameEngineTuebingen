#include "Light.h"

Light::Light(vec3 aPosition, vec3 aColor, vec3 aDirection, int aType)
{
	Position = aPosition;
	Color = aColor;
	Direction = aDirection;
	Type = aType;
}