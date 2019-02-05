#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>


/** \brief Constructor for a Transform instance

This constructor initiates transformations with no effect until change.
*/
Transform::Transform()
{
	Scale = vec3(1.0f);
	Rotation = quat(1, 0, 0, 0);
}

/** \brief Overloaded constructor for a Transform instance

This constructor changes the only position of the transformed object until change.
*/
Transform::Transform(vec3 aPosition) :Transform()
{
	Position = aPosition;
}

/** \brief Overloaded constructor for a Transform instance

This constructor changes only position and scale of the transformed object until change.
*/
Transform::Transform(vec3 aPosition, float aScale) :Transform()
{
	Position = aPosition;
	Scale = vec3(aScale);
}

/** \brief Overloaded constructor for a Transform instance

This constructor changes only position and scale of the transformed object until change.
*/
Transform::Transform(vec3 aPosition, vec3 aScale) :Transform()
{
	Position = aPosition;
	Scale = aScale;
}

/** \brief Get transformation matrix

This function provides the full transformation matrix: translation matrix * rotation matrix * scaling matrix
*/
mat4 Transform::GetMatrix()
{
	return translate(mat4(1), Position) * (mat4)Rotation * scale(mat4(1), Scale);
}
