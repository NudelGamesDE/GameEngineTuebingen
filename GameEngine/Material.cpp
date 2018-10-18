#include "Material.h"

#include <GL\glew.h>

void Material::Use()
{
	glColor4f(Color.r, Color.g, Color.b, Color.a);
}