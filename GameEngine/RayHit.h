#ifndef _RAYHIT_H
#define _RAYHIT_H

#include <memory>
#include "Renderer.h"
using namespace std;

/** \brief A ray hit

This struct describes a hit caused by a raycast hitting a mesh. It contains the distance and the renderer containing the mesh that has been hit.
*/
struct RayHit
{
	float DirectionDistance;
	shared_ptr<Renderer> RendererHit;
};

#else
struct RayHit;
#endif