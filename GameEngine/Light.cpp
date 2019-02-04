#include "Light.h"

/** \brief Constructor for a Light instance

\param aPosition the position of the light in 3D space
\param aColor a RGB color
\param aDirection the direction of the light
\param aType the type of the light (directional, point, spot)
*/
Light::Light(vec3 aPosition, vec3 aColor, vec3 aDirection, int aType)
{
	Position = aPosition;
	Color = aColor;
	Direction = aDirection;
	Type = aType;
}