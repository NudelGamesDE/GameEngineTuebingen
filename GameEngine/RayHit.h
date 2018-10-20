#ifndef _RAYHIT_H
#define _RAYHIT_H

#include <memory>
#include "Renderer.h"
using namespace std;

struct RayHit
{
	float DirectionDistance;
	shared_ptr<Renderer> RendererHit;
};

#else
struct RayHit;
#endif