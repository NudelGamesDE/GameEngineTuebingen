#ifndef _HARDWARE_H
#define _HARDWARE_H

#include <memory>
#include <ctime>
#include <unordered_set>
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_keycode.h>
#include <SDL_opengl.h>
#include "Game.h"
#include "FrameData.h"
#include "Engine.h"
#include <iostream>

using namespace std;
using namespace glm;

extern int FPS;
extern float render_time_in_ms;

class hardware
{
	public:
	static void render_time(clock_t starting_point, clock_t ending_point);
	static void frames_per_second(clock_t starting_point, clock_t ending_point);
};

#endif
